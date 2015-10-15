/* cdwMakePairedEndQa - Do alignments of paired-end fastq files and calculate distrubution of 
 * insert size. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */
#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "options.h"
#include "jksql.h"
#include "portable.h"
#include "obscure.h"
#include "cdw.h"
#include "cdwLib.h"
#include "raToStruct.h"
#include "ra.h"

int maxInsert = 1000;

void usage()
/* Explain usage and exit. */
{
errAbort(
  "cdwMakePairedEndQa - Do alignments of paired-end fastq files and calculate distrubution of \n"
  "insert size.\n"
  "usage:\n"
  "   cdwMakePairedEndQa startId endId\n"
  "options:\n"
  "   -maxInsert=N - maximum allowed insert size, default %d\n"
  , maxInsert
  );
}

/* Command line validation table. */
static struct optionSpec options[] = {
   {"maxInsert", OPTION_INT},
   {NULL, 0},
};

/**** - Start raToStructGen generated code - ****/

struct raToStructReader *cdwQaPairedEndFastqRaReader()
/* Make a raToStructReader for cdwQaPairedEndFastq */
{
static char *fields[] = {
    "fileId1",
    "concordance",
    "distanceMean",
    "distanceStd",
    "distanceMin",
    "distanceMax",
    };
static char *requiredFields[] = {
    "concordance",
    "distanceMean",
    "distanceStd",
    "distanceMin",
    "distanceMax",
    };
return raToStructReaderNew("cdwQaPairedEndFastq", ArraySize(fields), fields, ArraySize(requiredFields), requiredFields);
}


struct cdwQaPairedEndFastq *cdwQaPairedEndFastqFromNextRa(struct lineFile *lf, struct raToStructReader *reader)
/* Return next stanza put into an cdwQaPairedEndFastq. */
{
enum fields
    {
    fileId1Field,
    concordanceField,
    distanceMeanField,
    distanceStdField,
    distanceMinField,
    distanceMaxField,
    };
if (!raSkipLeadingEmptyLines(lf, NULL))
    return NULL;

struct cdwQaPairedEndFastq *el;
AllocVar(el);

bool *fieldsObserved = reader->fieldsObserved;
bzero(fieldsObserved, reader->fieldCount);

char *tag, *val;
while (raNextTagVal(lf, &tag, &val, NULL))
    {
    struct hashEl *hel = hashLookup(reader->fieldIds, tag);
    if (hel != NULL)
        {
	int id = ptToInt(hel->val);
	if (fieldsObserved[id])
	     errAbort("Duplicate tag %s line %d of %s\n", tag, lf->lineIx, lf->fileName);
	fieldsObserved[id] = TRUE;
	switch (id)
	    {
	    case fileId1Field:
	        {
	        el->fileId1 = sqlUnsigned(val);
		break;
	        }
	    case concordanceField:
	        {
	        el->concordance = sqlDouble(val);
		break;
	        }
	    case distanceMeanField:
	        {
	        el->distanceMean = sqlDouble(val);
		break;
	        }
	    case distanceStdField:
	        {
	        el->distanceStd = sqlDouble(val);
		break;
	        }
	    case distanceMinField:
	        {
	        el->distanceMin = sqlDouble(val);
		break;
	        }
	    case distanceMaxField:
	        {
	        el->distanceMax = sqlDouble(val);
		break;
	        }
	    default:
	        internalErr();
		break;
	    }
	}
    }

raToStructReaderCheckRequiredFields(reader, lf);
return el;
}


struct cdwQaPairedEndFastq *cdwQaPairedEndFastqLoadRa(char *fileName)
/* Return list of all cdwQaPairedEndFastq in ra file. */
{
struct raToStructReader *reader = cdwQaPairedEndFastqRaReader();
struct lineFile *lf = lineFileOpen(fileName, TRUE);
struct cdwQaPairedEndFastq *el, *list = NULL;
while ((el = cdwQaPairedEndFastqFromNextRa(lf, reader)) != NULL)
    slAddHead(&list, el);
slReverse(&list);
lineFileClose(&lf);
raToStructReaderFree(&reader);
return list;
}

struct cdwQaPairedEndFastq *cdwQaPairedEndFastqOneFromRa(char *fileName)
/* Return cdwQaPairedEndFastq in file and insist there be exactly one record. */
{
struct cdwQaPairedEndFastq *one = cdwQaPairedEndFastqLoadRa(fileName);
if (one == NULL)
    errAbort("No data in %s", fileName);
if (one->next != NULL)
    errAbort("Multiple records in %s", fileName);
return one;
}

/**** - End raToStructGen generated code - ****/

#define FASTQ_SAMPLE_SIZE 10000

void makeTmpSai(struct sqlConnection *conn, struct cdwValidFile *vf, char *genoFile, 
    char **retSampleFile, char **retSaiFile)
/* Given a fastq file, make a subsample of it 100k reads long and align it with
 * bwa producing a sai file of given name. */
{
/* Get fastq record */
long long fileId = vf->fileId;
struct cdwFastqFile *fqf = cdwFastqFileFromFileId(conn, fileId);
if (fqf == NULL)
    errAbort("No cdwFastqFile record for file id %lld", fileId);

/* Create downsampled fastq in temp directory - downsampled more than default even. */
char sampleFastqName[PATH_LEN];
cdwMakeTempFastqSample(fqf->sampleFileName, FASTQ_SAMPLE_SIZE, sampleFastqName);
verbose(1, "downsampled %s into %s\n", vf->licensePlate, sampleFastqName);

/* Do alignment */
char cmd[3*PATH_LEN];
char *saiName = cloneString(rTempName(cdwTempDir(), "cdwPairSample", ".sai"));
safef(cmd, sizeof(cmd), "bwa aln -t 3 %s %s > %s", genoFile, sampleFastqName, saiName);
mustSystem(cmd);

/* Save return variables, clean up,  and go home. */
*retSampleFile = cloneString(sampleFastqName);
*retSaiFile = saiName;
cdwFastqFileFree(&fqf);
}

void pairedEndQa(struct sqlConnection *conn, struct cdwFile *ef, struct cdwValidFile *vf)
/* Look for other end,  do a pairwise alignment, and save results in database. */
{
verbose(2, "pairedEndQa on %u %s %s\n", ef->id, ef->cdwFileName, ef->submitFileName);
/* Get other end, return if not found. */
struct cdwValidFile *otherVf = cdwOppositePairedEnd(conn, vf);
if (otherVf == NULL)
    return;

if (otherVf->fileId > vf->fileId)
    return;

struct cdwValidFile *vf1, *vf2;
struct cdwQaPairedEndFastq *pair = cdwQaPairedEndFastqFromVfs(conn, vf, otherVf, &vf1, &vf2);
if (pair != NULL)
    {
    cdwValidFileFree(&otherVf);
    return;
    }

/* Get target assembly and figure out path for BWA index. */
struct cdwAssembly *assembly = cdwAssemblyForUcscDb(conn, vf->ucscDb);
assert(assembly != NULL);
char genoFile[PATH_LEN];
safef(genoFile, sizeof(genoFile), "%s%s/bwaData/%s.fa", 
    cdwValDataDir, assembly->ucscDb, assembly->ucscDb);

verbose(1, "aligning subsamples on %u vs. %u paired reads\n", vf1->fileId, vf2->fileId);

/* Make alignments of subsamples. */
char *sample1 = NULL, *sample2 = NULL, *sai1 = NULL, *sai2 = NULL;
makeTmpSai(conn, vf1, genoFile, &sample1, &sai1);
makeTmpSai(conn, vf2, genoFile, &sample2, &sai2);

/* Make paired end alignment */
char *tmpSam = cloneString(rTempName(cdwTempDir(), "cdwPairSample", ".sam"));
char command[6*PATH_LEN];
safef(command, sizeof(command),
   "bwa sampe -n 1 -N 1 -f %s %s %s %s %s %s"
   , tmpSam, genoFile, sai1, sai2, sample1, sample2);
mustSystem(command);

/* Make ra file with pairing statistics */
char *tmpRa = cloneString(rTempName(cdwTempDir(), "cdwPairSample", ".ra"));
safef(command, sizeof(command), 
    "edwSamPairedEndStats -maxInsert=%d %s %s", maxInsert, tmpSam, tmpRa);
mustSystem(command);

/* Read RA file into variables. */
struct cdwQaPairedEndFastq *pe = cdwQaPairedEndFastqOneFromRa(tmpRa);

/* Update database with record. */
struct sqlConnection *freshConn = cdwConnectReadWrite();
char query[256];
sqlSafef(query, sizeof(query),
    "insert into cdwQaPairedEndFastq "
    "(fileId1,fileId2,concordance,distanceMean,distanceStd,distanceMin,distanceMax,recordComplete) "
    " values (%u,%u,%g,%g,%g,%g,%g,1)"
    , vf1->fileId, vf2->fileId, pe->concordance, pe->distanceMean
    , pe->distanceStd, pe->distanceMin, pe->distanceMax);
sqlUpdate(conn, query);
sqlDisconnect(&freshConn);

/* Clean up and go home. */
cdwValidFileFree(&otherVf);
remove(sample1);
remove(sample2);
remove(sai1);
remove(sai2);
remove(tmpSam);
remove(tmpRa);
#ifdef SOON
#endif /* SOON */
freez(&sample1);
freez(&sample2);
freez(&sai1);
freez(&sai2);
freez(&tmpSam);
freez(&tmpRa);
cdwQaPairedEndFastqFree(&pe);
cdwValidFileFree(&otherVf);
}

void cdwMakePairedEndQa(unsigned startId, unsigned endId)
/* cdwMakePairedEndQa - Do alignments of paired-end fastq files and calculate distrubution of 
 * insert size. */
{
struct sqlConnection *conn = cdwConnectReadWrite();
struct cdwFile *ef, *efList = cdwFileAllIntactBetween(conn, startId, endId);
for (ef = efList; ef != NULL; ef = ef->next)
    {
    struct cdwValidFile *vf = cdwValidFileFromFileId(conn, ef->id);
    if (vf != NULL)
	{
	if (sameString(vf->format, "fastq") && !isEmpty(vf->pairedEnd))
	    pairedEndQa(conn, ef, vf);
	}
    }
sqlDisconnect(&conn);
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, options);
if (argc != 3)
    usage();
maxInsert = optionInt("maxInsert", maxInsert);
cdwMakePairedEndQa(sqlUnsigned(argv[1]), sqlUnsigned(argv[2]));
return 0;
}

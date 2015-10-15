/* Parser to read in a cdwFastqFile from a ra file where tags in ra file correspond to fields in a
 * struct. This program was generated by raToStructGen. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "hash.h"
#include "obscure.h"
#include "sqlNum.h"
#include "sqlList.h"
#include "ra.h"
#include "raToStruct.h"
#include "cdw.h"

struct raToStructReader *cdwFastqFileRaReader()
/* Make a raToStructReader for cdwFastqFile */
{
static char *fields[] = {
    "sampleCount",
    "basesInSample",
    "readCount",
    "baseCount",
    "readSizeMean",
    "readSizeStd",
    "readSizeMin",
    "readSizeMax",
    "qualMean",
    "qualStd",
    "qualMin",
    "qualMax",
    "qualType",
    "qualZero",
    "atRatio",
    "aRatio",
    "cRatio",
    "gRatio",
    "tRatio",
    "nRatio",
    "qualPos",
    "aAtPos",
    "cAtPos",
    "gAtPos",
    "tAtPos",
    "nAtPos",
    };
static char *requiredFields[] = {
    "readCount",
    "baseCount",
    "readSizeMean",
    "readSizeStd",
    "readSizeMin",
    "readSizeMax",
    "qualMean",
    "qualStd",
    "qualMin",
    "qualMax",
    "qualType",
    "qualZero",
    "atRatio",
    "aRatio",
    "cRatio",
    "gRatio",
    "tRatio",
    "nRatio",
    "qualPos",
    "aAtPos",
    "cAtPos",
    "gAtPos",
    "tAtPos",
    "nAtPos",
    };
return raToStructReaderNew("cdwFastqFile", ArraySize(fields), fields, ArraySize(requiredFields), requiredFields);
}


struct cdwFastqFile *cdwFastqFileFromNextRa(struct lineFile *lf, struct raToStructReader *reader)
/* Return next stanza put into an cdwFastqFile. */
{
enum fields
    {
    sampleCountField,
    basesInSampleField,
    readCountField,
    baseCountField,
    readSizeMeanField,
    readSizeStdField,
    readSizeMinField,
    readSizeMaxField,
    qualMeanField,
    qualStdField,
    qualMinField,
    qualMaxField,
    qualTypeField,
    qualZeroField,
    atRatioField,
    aRatioField,
    cRatioField,
    gRatioField,
    tRatioField,
    nRatioField,
    qualPosField,
    aAtPosField,
    cAtPosField,
    gAtPosField,
    tAtPosField,
    nAtPosField,
    };
if (!raSkipLeadingEmptyLines(lf, NULL))
    return NULL;

struct cdwFastqFile *el;
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
	    case sampleCountField:
	        {
	        el->sampleCount = sqlLongLong(val);
		break;
	        }
	    case basesInSampleField:
	        {
	        el->basesInSample = sqlLongLong(val);
		break;
	        }
	    case readCountField:
	        {
	        el->readCount = sqlLongLong(val);
		break;
	        }
	    case baseCountField:
	        {
	        el->baseCount = sqlLongLong(val);
		break;
	        }
	    case readSizeMeanField:
	        {
	        el->readSizeMean = sqlDouble(val);
		break;
	        }
	    case readSizeStdField:
	        {
	        el->readSizeStd = sqlDouble(val);
		break;
	        }
	    case readSizeMinField:
	        {
	        el->readSizeMin = sqlSigned(val);
		break;
	        }
	    case readSizeMaxField:
	        {
                int arraySize = sqlSigned(val);
                raToStructArraySignedSizer(lf, arraySize, &el->readSizeMax, "readSizeMax");
		break;
	        }
	    case qualMeanField:
	        {
	        el->qualMean = sqlDouble(val);
		break;
	        }
	    case qualStdField:
	        {
	        el->qualStd = sqlDouble(val);
		break;
	        }
	    case qualMinField:
	        {
	        el->qualMin = sqlDouble(val);
		break;
	        }
	    case qualMaxField:
	        {
	        el->qualMax = sqlDouble(val);
		break;
	        }
	    case qualTypeField:
	        {
	        el->qualType = cloneString(val);
		break;
	        }
	    case qualZeroField:
	        {
	        el->qualZero = sqlSigned(val);
		break;
	        }
	    case atRatioField:
	        {
	        el->atRatio = sqlDouble(val);
		break;
	        }
	    case aRatioField:
	        {
	        el->aRatio = sqlDouble(val);
		break;
	        }
	    case cRatioField:
	        {
	        el->cRatio = sqlDouble(val);
		break;
	        }
	    case gRatioField:
	        {
	        el->gRatio = sqlDouble(val);
		break;
	        }
	    case tRatioField:
	        {
	        el->tRatio = sqlDouble(val);
		break;
	        }
	    case nRatioField:
	        {
	        el->nRatio = sqlDouble(val);
		break;
	        }
	    case qualPosField:
	        {
                int arraySize;
		sqlDoubleDynamicArray(val, &el->qualPos, &arraySize);
                raToStructArraySignedSizer(lf, arraySize, &el->readSizeMax, "qualPos");
		break;
	        }
	    case aAtPosField:
	        {
                int arraySize;
		sqlDoubleDynamicArray(val, &el->aAtPos, &arraySize);
                raToStructArraySignedSizer(lf, arraySize, &el->readSizeMax, "aAtPos");
		break;
	        }
	    case cAtPosField:
	        {
                int arraySize;
		sqlDoubleDynamicArray(val, &el->cAtPos, &arraySize);
                raToStructArraySignedSizer(lf, arraySize, &el->readSizeMax, "cAtPos");
		break;
	        }
	    case gAtPosField:
	        {
                int arraySize;
		sqlDoubleDynamicArray(val, &el->gAtPos, &arraySize);
                raToStructArraySignedSizer(lf, arraySize, &el->readSizeMax, "gAtPos");
		break;
	        }
	    case tAtPosField:
	        {
                int arraySize;
		sqlDoubleDynamicArray(val, &el->tAtPos, &arraySize);
                raToStructArraySignedSizer(lf, arraySize, &el->readSizeMax, "tAtPos");
		break;
	        }
	    case nAtPosField:
	        {
                int arraySize;
		sqlDoubleDynamicArray(val, &el->nAtPos, &arraySize);
                raToStructArraySignedSizer(lf, arraySize, &el->readSizeMax, "nAtPos");
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

struct cdwFastqFile *cdwFastqFileLoadRa(char *fileName)
/* Return list of all cdwFastqFile in ra file. */
{
struct raToStructReader *reader = cdwFastqFileRaReader();
struct lineFile *lf = lineFileOpen(fileName, TRUE);
struct cdwFastqFile *el, *list = NULL;
while ((el = cdwFastqFileFromNextRa(lf, reader)) != NULL)
    slAddHead(&list, el);
slReverse(&list);
lineFileClose(&lf);
raToStructReaderFree(&reader);
return list;
}

struct cdwFastqFile *cdwFastqFileOneFromRa(char *fileName)
/* Return cdwFastqFile in file and insist there be exactly one record. */
{
struct cdwFastqFile *one = cdwFastqFileLoadRa(fileName);
if (one == NULL)
    errAbort("No data in %s", fileName);
if (one->next != NULL)
    errAbort("Multiple records in %s", fileName);
return one;
}


/* gbSeq.c was originally generated by the autoSql program, which also 
 * generated gbSeq.h and gbSeq.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "gbSeq.h"


/* definitions for type column */
static char *values_type[] = {"EST", "mRNA", "PEP", NULL};
static struct hash *valhash_type = NULL;

/* definitions for srcDb column */
static char *values_srcDb[] = {"GenBank", "RefSeq", "Other", NULL};
static struct hash *valhash_srcDb = NULL;

void gbSeqStaticLoad(char **row, struct gbSeq *ret)
/* Load a row from gbSeq table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlUnsigned(row[0]);
ret->acc = row[1];
ret->version = sqlSigned(row[2]);
ret->size = sqlUnsigned(row[3]);
ret->gbExtFile = sqlUnsigned(row[4]);
ret->file_offset = sqlLongLong(row[5]);
ret->file_size = sqlUnsigned(row[6]);
ret->type = sqlEnumParse(row[7], values_type, &valhash_type);
ret->srcDb = sqlEnumParse(row[8], values_srcDb, &valhash_srcDb);
}

struct gbSeq *gbSeqLoad(char **row)
/* Load a gbSeq from row fetched with select * from gbSeq
 * from database.  Dispose of this with gbSeqFree(). */
{
struct gbSeq *ret;

AllocVar(ret);
ret->id = sqlUnsigned(row[0]);
ret->acc = cloneString(row[1]);
ret->version = sqlSigned(row[2]);
ret->size = sqlUnsigned(row[3]);
ret->gbExtFile = sqlUnsigned(row[4]);
ret->file_offset = sqlLongLong(row[5]);
ret->file_size = sqlUnsigned(row[6]);
ret->type = sqlEnumParse(row[7], values_type, &valhash_type);
ret->srcDb = sqlEnumParse(row[8], values_srcDb, &valhash_srcDb);
return ret;
}

struct gbSeq *gbSeqLoadAll(char *fileName) 
/* Load all gbSeq from a whitespace-separated file.
 * Dispose of this with gbSeqFreeList(). */
{
struct gbSeq *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileRow(lf, row))
    {
    el = gbSeqLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gbSeq *gbSeqLoadAllByChar(char *fileName, char chopper) 
/* Load all gbSeq from a chopper separated file.
 * Dispose of this with gbSeqFreeList(). */
{
struct gbSeq *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = gbSeqLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gbSeq *gbSeqCommaIn(char **pS, struct gbSeq *ret)
/* Create a gbSeq out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gbSeq */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->acc = sqlStringComma(&s);
ret->version = sqlSignedComma(&s);
ret->size = sqlUnsignedComma(&s);
ret->gbExtFile = sqlUnsignedComma(&s);
ret->file_offset = sqlLongLongComma(&s);
ret->file_size = sqlUnsignedComma(&s);
ret->type = sqlEnumComma(&s, values_type, &valhash_type);
ret->srcDb = sqlEnumComma(&s, values_srcDb, &valhash_srcDb);
*pS = s;
return ret;
}

void gbSeqFree(struct gbSeq **pEl)
/* Free a single dynamically allocated gbSeq such as created
 * with gbSeqLoad(). */
{
struct gbSeq *el;

if ((el = *pEl) == NULL) return;
freeMem(el->acc);
freez(pEl);
}

void gbSeqFreeList(struct gbSeq **pList)
/* Free a list of dynamically allocated gbSeq's */
{
struct gbSeq *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    gbSeqFree(&el);
    }
*pList = NULL;
}

void gbSeqOutput(struct gbSeq *el, FILE *f, char sep, char lastSep) 
/* Print out gbSeq.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->acc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->version);
fputc(sep,f);
fprintf(f, "%u", el->size);
fputc(sep,f);
fprintf(f, "%u", el->gbExtFile);
fputc(sep,f);
fprintf(f, "%lld", el->file_offset);
fputc(sep,f);
fprintf(f, "%u", el->file_size);
fputc(sep,f);
if (sep == ',') fputc('"',f);
sqlEnumPrint(f, el->type, values_type);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
sqlEnumPrint(f, el->srcDb, values_srcDb);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */


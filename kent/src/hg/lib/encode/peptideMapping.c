/* peptideMapping.c was originally generated by the autoSql program, which also 
 * generated peptideMapping.h and peptideMapping.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "peptideMapping.h"


void peptideMappingStaticLoad(char **row, struct peptideMapping *ret)
/* Load a row from peptideMapping table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->rawScore = sqlFloat(row[6]);
ret->spectrumId = row[7];
ret->peptideRank = sqlUnsigned(row[8]);
ret->peptideRepeatCount = sqlUnsigned(row[9]);
}

struct peptideMapping *peptideMappingLoad(char **row)
/* Load a peptideMapping from row fetched with select * from peptideMapping
 * from database.  Dispose of this with peptideMappingFree(). */
{
struct peptideMapping *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->rawScore = sqlFloat(row[6]);
ret->spectrumId = cloneString(row[7]);
ret->peptideRank = sqlUnsigned(row[8]);
ret->peptideRepeatCount = sqlUnsigned(row[9]);
return ret;
}

struct peptideMapping *peptideMappingLoadAll(char *fileName) 
/* Load all peptideMapping from a whitespace-separated file.
 * Dispose of this with peptideMappingFreeList(). */
{
struct peptideMapping *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[10];

while (lineFileRow(lf, row))
    {
    el = peptideMappingLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct peptideMapping *peptideMappingLoadAllByChar(char *fileName, char chopper) 
/* Load all peptideMapping from a chopper separated file.
 * Dispose of this with peptideMappingFreeList(). */
{
struct peptideMapping *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[10];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = peptideMappingLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct peptideMapping *peptideMappingCommaIn(char **pS, struct peptideMapping *ret)
/* Create a peptideMapping out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new peptideMapping */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->rawScore = sqlFloatComma(&s);
ret->spectrumId = sqlStringComma(&s);
ret->peptideRank = sqlUnsignedComma(&s);
ret->peptideRepeatCount = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void peptideMappingFree(struct peptideMapping **pEl)
/* Free a single dynamically allocated peptideMapping such as created
 * with peptideMappingLoad(). */
{
struct peptideMapping *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->spectrumId);
freez(pEl);
}

void peptideMappingFreeList(struct peptideMapping **pList)
/* Free a list of dynamically allocated peptideMapping's */
{
struct peptideMapping *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    peptideMappingFree(&el);
    }
*pList = NULL;
}

void peptideMappingOutput(struct peptideMapping *el, FILE *f, char sep, char lastSep) 
/* Print out peptideMapping.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->score);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%g", el->rawScore);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->spectrumId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->peptideRank);
fputc(sep,f);
fprintf(f, "%u", el->peptideRepeatCount);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */


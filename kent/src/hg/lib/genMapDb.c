/* genMapDb.c was originally generated by the autoSql program, which also 
 * generated genMapDb.h and genMapDb.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "genMapDb.h"


void genMapDbStaticLoad(char **row, struct genMapDb *ret)
/* Load a row from genMapDb table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlSigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
ret->accT7 = row[6];
ret->startT7 = sqlUnsigned(row[7]);
ret->endT7 = sqlUnsigned(row[8]);
strcpy(ret->strandT7, row[9]);
ret->accSP6 = row[10];
ret->startSP6 = sqlUnsigned(row[11]);
ret->endSP6 = sqlUnsigned(row[12]);
strcpy(ret->strandSP6, row[13]);
ret->stsMarker = row[14];
ret->stsStart = sqlUnsigned(row[15]);
ret->stsEnd = sqlUnsigned(row[16]);
}

struct genMapDb *genMapDbLoad(char **row)
/* Load a genMapDb from row fetched with select * from genMapDb
 * from database.  Dispose of this with genMapDbFree(). */
{
struct genMapDb *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlSigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
ret->accT7 = cloneString(row[6]);
ret->startT7 = sqlUnsigned(row[7]);
ret->endT7 = sqlUnsigned(row[8]);
strcpy(ret->strandT7, row[9]);
ret->accSP6 = cloneString(row[10]);
ret->startSP6 = sqlUnsigned(row[11]);
ret->endSP6 = sqlUnsigned(row[12]);
strcpy(ret->strandSP6, row[13]);
ret->stsMarker = cloneString(row[14]);
ret->stsStart = sqlUnsigned(row[15]);
ret->stsEnd = sqlUnsigned(row[16]);
return ret;
}

struct genMapDb *genMapDbLoadAll(char *fileName) 
/* Load all genMapDb from a tab-separated file.
 * Dispose of this with genMapDbFreeList(). */
{
struct genMapDb *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[17];

while (lineFileRow(lf, row))
    {
    el = genMapDbLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct genMapDb *genMapDbLoadWhere(struct sqlConnection *conn, char *table, char *where)
/* Load all genMapDb from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with genMapDbFreeList(). */
{
struct genMapDb *list = NULL, *el;
struct dyString *query = dyStringNew(256);
struct sqlResult *sr;
char **row;

sqlDyStringPrintf(query, "select * from %s", table);
if (where != NULL)
    dyStringPrintf(query, " where %s", where);
sr = sqlGetResult(conn, query->string);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = genMapDbLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
dyStringFree(&query);
return list;
}

struct genMapDb *genMapDbCommaIn(char **pS, struct genMapDb *ret)
/* Create a genMapDb out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new genMapDb */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlSignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->accT7 = sqlStringComma(&s);
ret->startT7 = sqlUnsignedComma(&s);
ret->endT7 = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strandT7, sizeof(ret->strandT7));
ret->accSP6 = sqlStringComma(&s);
ret->startSP6 = sqlUnsignedComma(&s);
ret->endSP6 = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strandSP6, sizeof(ret->strandSP6));
ret->stsMarker = sqlStringComma(&s);
ret->stsStart = sqlUnsignedComma(&s);
ret->stsEnd = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void genMapDbFree(struct genMapDb **pEl)
/* Free a single dynamically allocated genMapDb such as created
 * with genMapDbLoad(). */
{
struct genMapDb *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->accT7);
freeMem(el->accSP6);
freeMem(el->stsMarker);
freez(pEl);
}

void genMapDbFreeList(struct genMapDb **pList)
/* Free a list of dynamically allocated genMapDb's */
{
struct genMapDb *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    genMapDbFree(&el);
    }
*pList = NULL;
}

void genMapDbOutput(struct genMapDb *el, FILE *f, char sep, char lastSep) 
/* Print out genMapDb.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->chromStart);
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
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->accT7);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->startT7);
fputc(sep,f);
fprintf(f, "%u", el->endT7);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strandT7);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->accSP6);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->startSP6);
fputc(sep,f);
fprintf(f, "%u", el->endSP6);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strandSP6);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->stsMarker);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->stsStart);
fputc(sep,f);
fprintf(f, "%u", el->stsEnd);
fputc(lastSep,f);
}


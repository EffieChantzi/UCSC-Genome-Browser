/* vegaInfo.c was originally generated by the autoSql program, which also 
 * generated vegaInfo.h and vegaInfo.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "vegaInfo.h"


void vegaInfoStaticLoad(char **row, struct vegaInfo *ret)
/* Load a row from vegaInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->transcriptId = row[0];
ret->otterId = row[1];
ret->geneId = row[2];
ret->method = row[3];
ret->geneDesc = row[4];
}

struct vegaInfo *vegaInfoLoad(char **row)
/* Load a vegaInfo from row fetched with select * from vegaInfo
 * from database.  Dispose of this with vegaInfoFree(). */
{
struct vegaInfo *ret;

AllocVar(ret);
ret->transcriptId = cloneString(row[0]);
ret->otterId = cloneString(row[1]);
ret->geneId = cloneString(row[2]);
ret->method = cloneString(row[3]);
ret->geneDesc = cloneString(row[4]);
return ret;
}

struct vegaInfo *vegaInfoLoadAll(char *fileName) 
/* Load all vegaInfo from a tab-separated file.
 * Dispose of this with vegaInfoFreeList(). */
{
struct vegaInfo *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = vegaInfoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct vegaInfo *vegaInfoCommaIn(char **pS, struct vegaInfo *ret)
/* Create a vegaInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new vegaInfo */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->transcriptId = sqlStringComma(&s);
ret->otterId = sqlStringComma(&s);
ret->geneId = sqlStringComma(&s);
ret->method = sqlStringComma(&s);
ret->geneDesc = sqlStringComma(&s);
*pS = s;
return ret;
}

void vegaInfoFree(struct vegaInfo **pEl)
/* Free a single dynamically allocated vegaInfo such as created
 * with vegaInfoLoad(). */
{
struct vegaInfo *el;

if ((el = *pEl) == NULL) return;
freeMem(el->transcriptId);
freeMem(el->otterId);
freeMem(el->geneId);
freeMem(el->method);
freeMem(el->geneDesc);
freez(pEl);
}

void vegaInfoFreeList(struct vegaInfo **pList)
/* Free a list of dynamically allocated vegaInfo's */
{
struct vegaInfo *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    vegaInfoFree(&el);
    }
*pList = NULL;
}

void vegaInfoOutput(struct vegaInfo *el, FILE *f, char sep, char lastSep) 
/* Print out vegaInfo.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->transcriptId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->otterId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->method);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneDesc);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */


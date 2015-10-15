/* sgdClone.c was originally generated by the autoSql program, which also 
 * generated sgdClone.h and sgdClone.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "sgdClone.h"


void sgdCloneStaticLoad(char **row, struct sgdClone *ret)
/* Load a row from sgdClone table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->atccName = row[4];
}

struct sgdClone *sgdCloneLoad(char **row)
/* Load a sgdClone from row fetched with select * from sgdClone
 * from database.  Dispose of this with sgdCloneFree(). */
{
struct sgdClone *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->atccName = cloneString(row[4]);
return ret;
}

struct sgdClone *sgdCloneLoadAll(char *fileName) 
/* Load all sgdClone from a whitespace-separated file.
 * Dispose of this with sgdCloneFreeList(). */
{
struct sgdClone *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = sgdCloneLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct sgdClone *sgdCloneLoadAllByChar(char *fileName, char chopper) 
/* Load all sgdClone from a chopper separated file.
 * Dispose of this with sgdCloneFreeList(). */
{
struct sgdClone *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = sgdCloneLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct sgdClone *sgdCloneCommaIn(char **pS, struct sgdClone *ret)
/* Create a sgdClone out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new sgdClone */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->atccName = sqlStringComma(&s);
*pS = s;
return ret;
}

void sgdCloneFree(struct sgdClone **pEl)
/* Free a single dynamically allocated sgdClone such as created
 * with sgdCloneLoad(). */
{
struct sgdClone *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->atccName);
freez(pEl);
}

void sgdCloneFreeList(struct sgdClone **pList)
/* Free a list of dynamically allocated sgdClone's */
{
struct sgdClone *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    sgdCloneFree(&el);
    }
*pList = NULL;
}

void sgdCloneOutput(struct sgdClone *el, FILE *f, char sep, char lastSep) 
/* Print out sgdClone.  Separate fields with sep. Follow last field with lastSep. */
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
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->atccName);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */


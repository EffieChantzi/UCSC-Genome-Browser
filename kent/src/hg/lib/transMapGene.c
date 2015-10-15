/* transMapGene.c was originally generated by the autoSql program, which also 
 * generated transMapGene.h and transMapGene.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "transMapGene.h"

char *transMapGeneCommaSepFieldNames4 = "id,cds,db,geneName";   // previous version without geneId column
char *transMapGeneCommaSepFieldNames = "id,cds,db,geneName,geneId";

void transMapGeneStaticLoad(char **row, struct transMapGene *ret)
/* Load a row from transMapGene table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = row[0];
ret->cds = row[1];
safecpy(ret->db, sizeof(ret->db), row[2]);
ret->geneName = row[3];
ret->geneId = row[4];
}

struct transMapGene *transMapGeneLoad(char **row)
/* Load a transMapGene from row fetched with select * from transMapGene
 * from database.  Dispose of this with transMapGeneFree(). */
{
struct transMapGene *ret;

AllocVar(ret);
ret->id = cloneString(row[0]);
ret->cds = cloneString(row[1]);
safecpy(ret->db, sizeof(ret->db), row[2]);
ret->geneName = cloneString(row[3]);
ret->geneId = cloneString(row[4]);
return ret;
}

struct transMapGene *transMapGeneLoadAll(char *fileName) 
/* Load all transMapGene from a whitespace-separated file.
 * Dispose of this with transMapGeneFreeList(). */
{
struct transMapGene *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = transMapGeneLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct transMapGene *transMapGeneLoadAllByChar(char *fileName, char chopper) 
/* Load all transMapGene from a chopper separated file.
 * Dispose of this with transMapGeneFreeList(). */
{
struct transMapGene *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = transMapGeneLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct transMapGene *transMapGeneCommaIn(char **pS, struct transMapGene *ret)
/* Create a transMapGene out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new transMapGene */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlStringComma(&s);
ret->cds = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->db, sizeof(ret->db));
ret->geneName = sqlStringComma(&s);
ret->geneId = sqlStringComma(&s);
*pS = s;
return ret;
}

void transMapGeneFree(struct transMapGene **pEl)
/* Free a single dynamically allocated transMapGene such as created
 * with transMapGeneLoad(). */
{
struct transMapGene *el;

if ((el = *pEl) == NULL) return;
freeMem(el->id);
freeMem(el->cds);
freeMem(el->geneName);
freeMem(el->geneId);
freez(pEl);
}

void transMapGeneFreeList(struct transMapGene **pList)
/* Free a list of dynamically allocated transMapGene's */
{
struct transMapGene *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    transMapGeneFree(&el);
    }
*pList = NULL;
}

void transMapGeneOutput(struct transMapGene *el, FILE *f, char sep, char lastSep) 
/* Print out transMapGene.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->id);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->cds);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->db);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

struct transMapGene *transMapGeneQuery(struct sqlConnection *geneConn,
                                       char *table, char *srcDb, char *srcId)
/* load a single transMapSrc object for an srcDb and srcId from a table,
 * or return NULL if not found */
{
/* geneId field was added after original table definition.  Return empty string
 * in query for legacy tables. */
if (sqlFieldIndex(geneConn, table, "geneId") >= 0)
    return sqlQueryObjs(geneConn, (sqlLoadFunc)transMapGeneLoad,
                        sqlQuerySingle,
                        "SELECT %-s FROM %s WHERE (db=\"%s\") and (id = \"%s\")",
                        transMapGeneCommaSepFieldNames, table, srcDb, srcId);
else
    return sqlQueryObjs(geneConn, (sqlLoadFunc)transMapGeneLoad,
                        sqlQuerySingle,
                        "SELECT %-s,\"\" FROM %s WHERE (db=\"%s\") and (id = \"%s\")",
                        transMapGeneCommaSepFieldNames4, table, srcDb, srcId);
}

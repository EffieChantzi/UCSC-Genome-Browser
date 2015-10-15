
#include "common.h"
#include "hCommon.h"
#include "hgc.h"


/* 
 * This method uses curl to include a section with a specified header and url (should return html)
 * The section header and url are defined in the track lines as:
 * track trackName
 * ....
 * section http://localhost/cgi-bin/listPathways.py?geneid=$$ 
 * sectionHeader Kegg Pathways
 * The $$ placeholder is replaced with the itemName(e.g. geneName) as well as the url parameters of the current viewed page
 * These parameters should be sessionID (hgsid), chromosome(c),opening position(o), terminal position (t) and track name (g)
 * e.g. hgsid=116_MDRtHy01prLXOVvit66nQyxIPati&c=JYIM01000001&o=2485&t=3372&g=CDS&i=Lokiarch_00040
 * The script can use this information to redirect the user to another item if need be or just ignore the extra parameters
 */
void printSection(struct trackDb *tdb, char *itemName, char *section, char *organism)
{  
  char sectionHeaderSetting[32];
  
  /* create the url label setting for trackDb from the url
   setting prefix */
  safef(sectionHeaderSetting, sizeof(sectionHeaderSetting), "%sHeader", section);
  
  /*Fetch the value of the sectionHeader for the track*/
  char *header = trackDbSettingOrDefault(tdb, sectionHeaderSetting, "Custom Section:");
  
    /*Print the section Header*/
  printf("<table style=\"text-align: left; width: 99%%;\" border=\"1\" cellpadding=\"5\" cellspacing=\"0\">\n");
  printf("<tbody><tr><td style=\"background-color:#eee9e9;\">\n");
  printf("<b>%s</b><br></td></tr>\n", header);
  printf("<tr><td>\n");
  
  
  // replace the $$ and other wildcards with the url given in tdb 
  char* sectionUrl= constructUrl(tdb, section, itemName, FALSE);
  char curUrl[299];
  sprintf(curUrl,"db=%s&hgsid=%s&c=%s&o=%s&t=%s&g=%s",organism,cartSessionId(cart), cartString(cart,"c"),cartString(cart,"o"),cartString(cart,"t"),cartString(cart,"g"));
  char sectionUrlTemp[300];
  sprintf(sectionUrlTemp, "%s&%s", sectionUrl, curUrl);
  
  if (sectionUrl==NULL)
    return;
 
  
  /*create the command to fetch the URL using curl*/
  char cmd[300];
  sprintf(cmd,"curl --url '%s'", sectionUrlTemp);
  /*Load Section Body from URL*/ 
  char *sectionData  = system(cmd);
  if (sectionData){
    printf("<br>\n%s\n<br>", sectionData);
  }
  /*Section Footer*/
  printf("</td></tr></tbody></table><br>\n");

}


void doThijsLabCDS(struct trackDb *tdb, char *geneName,char *organism)
{
      
      struct sqlConnection *conn = hAllocConn(database);
      int start = cartInt(cart, "o");

      char *headerItem = cloneString(geneName);
      genericHeader(tdb, headerItem);
      printCustomUrl(tdb, geneName, FALSE);   
      genericGenePredClick(conn, tdb, geneName, start, NULL, NULL);
      printSection(tdb, geneName, "keggSection",organism);    
      printTrackHtml(tdb);
      
      hFreeConn(&conn);
}



bool thijsLabClick(char *track, char *item, struct trackDb *tdb, char *organism)
{
    
    if (sameWord(track, "CDS"))
    {    
	doThijsLabCDS(tdb, item,organism);
    }
    else if (tdb != NULL)
    {      
      genericClickHandler(tdb, item, NULL);
    }
    else
    {
      cartWebStart(cart, database, "%s", track);
      printf("Sorry, clicking there doesn't do anything yet (%s).", track);
    }
    return TRUE;
}

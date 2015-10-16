#! /usr/bin/python2.7

import cgitb
cgitb.enable()
import os
import MySQLdb
import urlparse


# imports for handling KGML files
from Bio.KEGG.REST import *
from Bio.KEGG.KGML import KGML_parser
from Bio.Graphics.KGML_vis import KGMLCanvas
from wand.image import Image
from wand.color import Color
from parseConfig import sqlConnect

print "Content-type:text/html\r\n\r\n"
print '<html>'
print '<head>'
print '''

<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
<script type="text/javascript" src="../js/zoom.js"></script>
<link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

<script type="text/javascript">
jQuery(document).ready(function($){ //fire on DOM ready
var c = 0;
$('#zoomBtn').click(function(){

       if (c == 0){
        $('#path_im').addpowerzoom({magnifiersize: [450, 450]});
        c = 1
       }
       else{
       $('#path_im').addpowerzoom({magnifiersize: [0, 0]});
       c = 0
       }
    });
});
</script>

<style type="text/css">
.gapClass{margin-left:78%;}
</style>

'''

URL = os.environ["REQUEST_URI"]
parsedURL = urlparse.urlparse(URL)

tmp_path = (parsedURL.query).split('=')[1]
pathMap = tmp_path.split('&')[0]
tmp_gene = (parsedURL.query).split('=')[2]
gene = tmp_gene.split('&')[0]
tmp_db = (parsedURL.query).split('=')[3]
orgDB = tmp_db.split('&')[0]



print '''
<title>Pathway Map</title>
</head>
<body>

<div class="panel panel-primary">
<div class="panel-heading">%s_%s <b class="gapClass"></b> <button type="button" class="btn btn-primary btn-lg" id="zoomBtn" style="margin-left: 20px;">
<span class="glyphicon glyphicon-zoom-in"></span> &nbsp; <span class="glyphicon glyphicon-zoom-out"></span></button></div>''' % (pathMap, gene)
print '</div>'



def drawPathway(geneID, orgDB, pathID):

    pathway = KGML_parser.read(kegg_get(pathID, "kgml"))

    db = sqlConnect( 'hgcentral','local')
    cursor = db.cursor()

    # This query is executed in order to show the pathways, orthology and geneID of the those genes that participate in the metabolic
    # pathway(s) of the initially requested LokiArchaea gene. It returns both the requested gene + ortholog genes for drawing purposes.
    sql = "SELECT k1.pathwayID, k1.orthologID, l1.name, k1.EC FROM KEGG_PathwayList k1, {db}.org_kegg_data l1 WHERE k1.orthologID=l1.orthologID AND k1.pathwayID IN (SELECT k.pathwayID FROM KEGG_PathwayList k, {db}.org_kegg_data l WHERE k.orthologID = l.orthologID AND l.name = '{gene}' AND k.pathwayID = '{pathway}')".format(db = orgDB, gene= geneID, pathway=pathID)
    cursor.execute(sql)

    data_genes = cursor.fetchall()

    check_nameFile = ''.join([pathID, '_', geneID, '.png'])
    os.chdir("../imPathways")
    if not os.path.exists(check_nameFile):
        for j in data_genes:
            for element_o in pathway.orthologs:
                ortholog = ''.join(['ko:', j[1]])
                if ortholog in element_o._names:
                    for graphic_o in element_o.graphics:
                        # if-else for coloring
                        # gene of interest
                        if j[2] == geneID:
                            # if pathway is a line diagram
                            if graphic_o.type == "line":
                                graphic_o.fgcolor = '#ff0000'
                                graphic_o.width = 4
                            else:
                                graphic_o.bgcolor = '#ff0000'

                        else:
                            if graphic_o.type == "line":
                                if graphic_o.fgcolor != '#ff0000':
                                    graphic_o.fgcolor = '#ffd700'
                                    graphic_o.width = 2
                            else:
                                if graphic_o.bgcolor != '#ff0000':
                                    graphic_o.bgcolor = '#ffd700'

                        # if-else for naming
                        tmp = j[2]
                        if j[3] != "":
                            if graphic_o.name.startswith("K"):
                                graphic_o.name = ''.join([j[3], '/', 'LA', tmp[8: len(tmp)]])
                            else:
                                if ('L' in graphic_o.name):
                                    graphic_o.name = ''.join([graphic_o.name, tmp[8: len(tmp)]])

                                elif graphic_o.name.startswith("N"):
                                    graphic_o.name = ''.join([graphic_o.name, '_', j[3], '/', 'LA', tmp[8: len(tmp)]])

                                else:
                                    graphic_o.name = ''.join(['LA', tmp[8: len(tmp)]])
                        else:
                            if graphic_o.name.startswith("N"):
                                graphic_o.name = ''.join([graphic_o.name, tmp[8: len(tmp)]])
                            else:
                                graphic_o.name = ''.join(['N', j[1]])

        for element_o in pathway.orthologs:
            for graphic_o in element_o.graphics:
		count = 0
                if graphic_o.type == "line":
                    if graphic_o.fgcolor == '#ff0000' or graphic_o.fgcolor == '#ffd700':

                        numGenes = graphic_o.name.count('_')
                        splitted = graphic_o.name.split('_')

			if graphic_o.name.startswith("N"):
				numGenes = numGenes + 1

                        if numGenes > 1:
                            for e in splitted:
                                if '/' in e:
                                    count = count + 1
                                    ec = e.split('/')[0]
                                    graphic_o.name = ''.join([ec, ' ', '(', str(numGenes), ')'])
                                if count == 0:
                                    if graphic_o.name.startswith("N"):
                                        ec = splitted[0]
                                        graphic_o.name = ''.join([ec[1 : len(ec)], ' ', '(', str(numGenes), ')'])
                        else:
                            for e in splitted:
                                if '/' in e:
                                    count = count + 1
                                    ec = e.split('/')[0]
                                    graphic_o.name = ec
                                if count == 0:
                                    if graphic_o.name.startswith("N"):
                                        ec = splitted[0]
                                        graphic_o.name = ec[1 : len(ec)]

                else:
                    if graphic_o.bgcolor == '#ff0000' or graphic_o.bgcolor == '#ffd700':
                        numGenes = graphic_o.name.count('_')
                        splitted = graphic_o.name.split('_')

			if graphic_o.name.startswith("N"):
                                numGenes = numGenes + 1

                        if numGenes > 1:
                            for e in splitted:
                                if '/' in e:
                                    count = count + 1
                                    ec = e.split('/')[0]
                                    graphic_o.name = ''.join([ec, ' ', '(', str(numGenes), ')'])
                                if count == 0:
                                    if graphic_o.name.startswith("N"):
                                        ec = splitted[0]
                                        graphic_o.name = ''.join([ec[1 : len(ec)], ' ', '(', str(numGenes), ')'])

                        else:
                            for e in splitted:
                                if '/' in e:
                                    count = count + 1
                                    ec = e.split('/')[0]
                                    graphic_o.name = ec
                                if count == 0:
                                    if graphic_o.name.startswith("N"):
                                        ec = splitted[0]
                                        graphic_o.name = ec[1 : len(ec)]


        canvas = KGMLCanvas(pathway, import_imagemap=True, label_compounds=False, label_maps=False, fontsize=8,
                        show_genes=False, show_orthologs=True)
        img_filename = "%s_%s.pdf" % (pathID, geneID)

        canvas.draw(img_filename)
        with Image(filename=img_filename, resolution=300) as img:
            with Image(width=img.width, height=img.height, background=Color("white")) as bg:
                bg.composite(img, 0, 0)
                bg.save(filename=check_nameFile)
                os.remove(img_filename)


    os.chdir('../cgi-bin')
    return check_nameFile


def displayPathway(ImName):
    imDir = ''.join(['../imPathways/', ImName])
    data_uri = open(imDir, 'rb').read().encode('base64').replace('\n', '')
    img_tag = '<img id = "path_im" src="data:image/png;base64,{0}" width="1350" height="1200">'.format(data_uri)
    print (img_tag)


# call function "findPathways" with argument the gene that has been requested
ImName = drawPathway(gene, orgDB, pathMap)

displayPathway(ImName)

print '</body>'
print '</html>'

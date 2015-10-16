#! /usr/bin/python2.7
import cgitb
cgitb.enable()
import os
import MySQLdb
import urlparse
from parseConfig import sqlConnect

#imports for handling KGML files
from Bio.KEGG.REST import *
from Bio.KEGG.KGML import KGML_parser
from Bio.Graphics.KGML_vis import KGMLCanvas
from pprint import pprint
from wand.image import Image
from wand.color import Color


def listPaths(geneID, orgDB, params):

	try:
		conn =  sqlConnect('hgcentral','local')

		if conn.open:
			cursor  = conn.cursor()
			sql = "SELECT k.pathwayID, k.orthologID, l.name FROM KEGG_PathwayList k, {db}.org_kegg_data l WHERE k.orthologID = l.orthologID AND l.name = '{gene}'".format(db = orgDB, gene = geneID)
			cursor.execute(sql)
			# fetch all of the rows from the query
			data_gene = cursor.fetchall ()
			rows_data_gene = cursor.rowcount

			print '<br/>'
			if rows_data_gene > 0:

				count = 0


				#This query is executed in order to show the other genes that are included in the KEGG Pathway(s) of the initially requested gene.
				#It returns all the LokiArchaea genes included in the KEGG Pathway(s) apart from the initially requested gene.



				for i in data_gene:
					sql = "SELECT DISTINCT(l1.name) FROM KEGG_PathwayList k1, {db}.org_kegg_data l1 WHERE  k1.orthologID = l1.orthologID AND l1.name != '{gene}' AND k1.pathwayID IN (SELECT k.pathwayID FROM KEGG_PathwayList k, {db}.org_kegg_data l WHERE k.orthologID = l.orthologID AND l.name = '{gene}' AND k.pathwayID = '{pathway}')".format(gene=geneID, db=orgDB, pathway =  i[0])
					cursor.execute(sql)
					data_genes = cursor.fetchall ()
					rows_data_genes = cursor.rowcount
					count = count + 1

					if rows_data_genes >= 1:

						print '''
					   	<div class="container">
						<div class="panel-group">
					    	<div class="panel panel-default">
					    	<div class="panel-heading">

						<button type="button" class="btn btn-primary" onclick = "window.open('Path.py?mapid=%s&geneid=%s&orgDB=%s')">%s_%s</button> <b class = gapClass></b> <button type="button" class="btn btn-primary" data-toggle="collapse" href = "#collapse%s" aria-expanded="false"><span class="caret"></span></button>''' % (i[0], i[2], orgDB, i[0], i[2], count)

					    	print '''
						</div>
						</div>
					    	<div id="collapse%s" class="panel-collapse collapse"> ''' % count
					    	print '<ul class="list-group">'
					    	print '<li class="dropdown-header">Pathway %s (%s)</li>' % (i[0], rows_data_genes)
					    	for j in data_genes:
					      		print '<li class="list-group-item list-group-item-info"> <a class="dropdown-item" href= "thijslab?%s&i=%s" style="color:#0000CC; text-decoration:none;">%s </a></li>'  % (params,j[0], j[0])
					    	print '</ul>'
					    	print '</div>'
					    	print '</div>'
					    	print '</div>'
						print '</div>'


			else:
				print '''
				<p>No pathways found.</p>
				<br/>


			</body>
			</html>
			'''
	except:
		print 'Database Error Connection'

print "Content-type:text/html\r\n\r\n"
#print  "Content-Type: text/plain;charset=utf-8"
print '''
<html>
<head>
<title>Pathway List</title>

<link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>

<style type="text/css">
.gapClass{margin-left:850px;}
</style>

</head>
<body>
'''

URL = os.environ["REQUEST_URI"]

parsedURL = urlparse.urlparse(URL)
params = (parsedURL.query).split('&',2)
geneID = params[0].split("=")[1]
orgDB = params[1].split("=")[1]
params.remove(params[0])

params.remove(params[0])


listPaths(geneID,orgDB,params[0])

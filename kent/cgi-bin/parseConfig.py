import MySQLdb
# these are default python modules on python 2.7, no errors expected here
import urllib, urllib2, zlib, collections, StringIO, gzip, string, sys, os, random, \
    subprocess, re, types, socket, cPickle, copy, glob

from collections import defaultdict, namedtuple
from os.path import *
from distutils import spawn

hgConf = None

def parseConf(fname):
    " parse a hg.conf style file, return as dict key -> value (all strings) "
    conf = {}
    for line in open(fname):
        line = line.strip()
        if line.startswith("#"):
            continue
        elif line.startswith("include "):
            inclFname = line.split()[1]
            inclPath = abspath(join(dirname(fname), inclFname))
            if isfile(inclPath):
                inclDict = parseConf(inclPath)
                conf.update(inclDict)
        elif "=" in line: # string search for "="
            key, value = line.split("=")
            conf[key] = value
    return conf


def parseHgConf():
    """ return hg.conf as dict key:value """
    global hgConf
    if hgConf is not None:
        return hgConf

    hgConf = dict() # python dict = hash table

    confDir = dirname(__file__)
    fname = join(confDir, "hg.conf")
    hgConf = parseConf(fname)

    return hgConf

def sqlConnect(db, name):
    """ connect to sql """
    if name=="public":
        host, user, passwd = "genome-mysql.cse.ucsc.edu", "genomep", "password"
    elif name=="local":
        cfg = parseHgConf()        
        host, user, passwd = cfg["db.host"], cfg["db.user"], cfg["db.password"]
    conn = MySQLdb.connect(host=host, user=user, passwd=passwd, db=db)
    return conn
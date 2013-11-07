#!/usr/bin/env python 

import xml.dom.minidom 

def fun():
    XMLDOM = xml.dom.minidom.parse("identity.xml") 
    organizations = xmldom.getElementsByTagName('DW') 
    for org in organizations: 
     products = org.getElementsByTagName('linux') 
    for product in products: 
        print 'ID: ' + product.getAttribute('id') 
        print 'Name: ' + product.getAttribute('name') 
        print 'Word Count: ' + product.getAttribute('count') 

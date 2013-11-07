#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

import BaseHTTPServer
import CGIHTTPServer
import cgitb; cgitb.enable()

server_address = ("", 8000)
handler = CGIHTTPServer.CGIHTTPRequestHandler
handler.cgi_directories = [""]
httpd = BaseHTTPServer.HTTPServer(server_address, handler)
httpd.serve_forever()

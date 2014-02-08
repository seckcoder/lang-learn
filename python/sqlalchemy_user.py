#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com


import sqlalchemy
from sqlalchemy import create_engine, Column, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
engine = create_engine('mysql://liwei@localhost/test', echo=True)
Base = declarative_base()
Base.metadata.bind = engine
class User(Base):
    __tablename__ = 'user'
    id = Column(Integer, primary_key=True)
    name = Column(String(1024))
    fullname = Column(String(1024))
    password = Column(String(1024))
    def __init__(self, name, fullname, password):
        self.name = name
        self.fullname = fullname
        self.password = password
    def __repr__(self):
        return "<User('%s','%s', '%s')>" % (self.name, self.fullname, self.password)

#Base.metadata.drop_all()
#Base.metadata.create_all(engine)
#print engine.table_names()
ed_user = User('ed', 'Ed Jones', 'edpassword')
Session = sessionmaker()
sess = Session(bind=engine, autoflush=True)
#sess.add(ed_user)
#our_user = sess.query(User).filter_by(name='ed').first()
#assert ed_user is our_user
#print ed_user
#print our_user
#for inst in sess.query(User).order_by(User.id):
    #print inst
print dir(sess.query(User))

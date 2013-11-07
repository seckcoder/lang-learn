from __future__ import absolute_import

from celery import Celery

celery = Celery('proj.celery',
                #broker='redis://10.1.9.9:6379',
                #backend='redis://10.1.9.9:6379',
                #include=['proj.tasks']
                )
from proj import celery_config
celery.config_from_object(celery_config)

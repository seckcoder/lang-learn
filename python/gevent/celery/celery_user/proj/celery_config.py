from __future__ import absolute_import

from datetime import timedelta
from celery.schedules import crontab
#BROKER_URL = "redis://10.1.9.9:6379"
BROKER_URL = "redis://127.0.0.1:6379"
#CELERY_RESULT_BACKEND = "redis://10.1.9.9:6379"
CELERY_RESULT_BACKEND = "redis://127.0.0.1:6379"
CELERY_ENALBE_UTC = True
CELERY_TIMEZONE = 'Asia/Shanghai'
CELERY_TASK_RESULT_EXPIRES = 8 * 24 * 60 * 60  # expire task in 8 days
CELERY_TRACK_STARTED = True

CELERY_IMPORTS = ("proj.tasks",)

CELERYD_TASK_TIME_LIMIT = 3600  # one hour
CELERYD_TASK_SOFT_TIME_LIMIT = 1800  # half an hour

CELERY_STORE_ERRORS_EVEN_IF_IGNORED = True

CELERY_SEND_TASK_ERROR_EMAILS = False
ADMINS = (
    ("wangdapeng", "wangdapeng@jike.com"),
    ("guoshaosong", "guoshaosong@jike.com"),
    ("liwei", "liwei@jike.com"),
)

SERVER_EMAIL = "testsinaweiboapi@gmail.com"

EMAIL_HOST = "smtp.gmail.com"
EMAIL_PORT = 25

CELERYBEAT_SCHEDULE = {
    'task_add_periodic' : {
        'task' : 'proj.tasks.add',
        'schedule' : timedelta(seconds=2),
        'args' : (16, 16)
    },
}

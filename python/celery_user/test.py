from proj.tasks import add
from datetime import datetime, timedelta
#res = add.delay(4, 4)
res = add.apply_async(args=[4], countdown=1)
print res.get()
next_time = datetime.utcnow() + timedelta(seconds=3)
print next_time
print datetime.now()
res = add.apply_async(args=[3, 5], eta=next_time)
print res.get()

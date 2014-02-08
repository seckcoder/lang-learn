#!/usr/bin/python
from celery import subtask
from celery import group, chain, chord, chunks
from proj.tasks import add, mul, add_callback, add_callback_noarg,\
        add_exc_callback, add_exc, xsum, StudyCase, X


#sub = add.subtask((2, 2))
#sub.delay()

#sub2 = add.subtask((3, 3), link=add_callback_noarg.subtask(countdown=2, immutable=True), countdown=2)
#sub2.delay()

#sub = (add.subtask((2, 2), countdown=10) | add.si(3,3).set(countdown=10))
#sub()
#sub.apply_async(countdown=20)
#sub = group([add.s(i, i) for i in xrange(10)])
#sub.apply_async(countdown=10)
#sub = (add.s(2, 2) | add.s(3,))
#print chain(add.s(2,2), add.s(3,)).apply_async(countdown=10).get()
#chord((add.s(i, i) for i in xrange(10)), xsum.s()).apply_async(countdown=10)
#group(add.s(4, 4) , add.s(3, 9)).apply_async(countdown=10)


#add_exc.subtask((2, 2), link_error=add_exc_callback.s()).delay()

#case = StudyCase()

#case.add_class.subtask((2, 2), link=case.add_class_callback.subtask(),
                       #link_error=case.add_class_exc_callback.subtask()).delay()

x = X()
print x.add.s(2,2).delay().get()

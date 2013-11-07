from celery import subtask
from celery import group, chain, chord, chunks
from proj import tasks
# Get subtask
## method 1
sub1 = subtask(tasks.add, args=(2, 2), countdown=1)
res = sub1.apply_async()
#print res.get()

## method 2
sub = tasks.add.subtask((2, 2), countdown=1)
res = sub.apply_async()
#print res.get()

## method 3
#print tasks.add.s(2, 2).set(countdown=1).apply_async().get()


# Partials
partial = tasks.add.s(2)
#print partial.delay(2).get()


# Immutbility
#sub = tasks.add.apply_async((2, 2), link=tasks.add_callback_noarg.subtask(immutable=True))
sub = tasks.add.apply_async((2, 2), link=tasks.add_callback_noarg.si())
#sub.get()


# Callbacks
sub = tasks.add.apply_async((2, 2), link=tasks.minus.s(3))
#print sub.get()

# Primitives
## Group
res = group(tasks.add.s(i, i) for i in xrange(10))()
#print res.get(timeout=1)

g = group(tasks.add.s(i, i) for i in xrange(4))
res = g.apply_async(countdown=2)
#print res.get()


## Chain
res = chain(tasks.add.s(2, 2), tasks.add.s(4), tasks.add.s(8))()
#print res.get()
#print res.parent.get()
#print res.parent.parent.get()

#print (tasks.add.s(2, 2) | tasks.add.s(4) | tasks.add.s(8))().get()


### Chain of independent tasks
res = chain(tasks.add.si(2, 2), tasks.add.si(4, 4), tasks.add.si(8, 8))()
#print res.get()
#print res.parent.get()
#print res.parent.parent.get()


## Chord
res = chord((tasks.add.s(i, i) for i in xrange(10)), tasks.xsum.s())()
#print res.get()

res = chord(tasks.add.s(i, i) for i in xrange(10))(tasks.xsum.s())
#print res.get()
# ===> break down
callback = tasks.xsum.s()
header = [tasks.add.s(i, i) for i in xrange(10)]
res = chord(header)(callback)
#print res.get()

### Chord with group and chain
c = (group(tasks.add.s(i, i) for i in xrange(10)) | tasks.xsum.s())
#print c().get()


## Map
res = tasks.xsum.map([xrange(10), xrange(20)]).delay()
#print res.get()

## starmap
res = tasks.add.starmap([(0, 0), (1, 1), (2, 2)]).delay()
#print res.get()

## Combining
c = (tasks.add.s(4, 16) | tasks.mul.s(2) | (tasks.add.s(4) | tasks.mul.s(8)))
#print c().get()

## Chunks
res = tasks.add.chunks([(0, 0), (1, 1), (2, 2), (3, 3)], 2)()
#print res.get()

"""
The following code is from celery
"""
def items(d):                   # noqa
    return d.iteritems()

def with_metaclass(Type, skip_attrs=set(['__dict__', '__weakref__'])):
    """Class decorator to set metaclass.

    Works with both Python 3 and Python 3 and it does not add
    an extra class in the lookup order like ``six.with_metaclass`` does
    (that is -- it copies the original class instead of using inheritance).

    """

    def _clone_with_metaclass(Class):
        attrs = dict((key, value) for key, value in items(vars(Class))
                     if key not in skip_attrs)
        return Type(Class.__name__, Class.__bases__, attrs)

    return _clone_with_metaclass

tasks = {}
def gen_task_name():
    """
    Celery has better way of getting task name, this is just a demo
    """
    return "default tasks"
def register(task):
    import inspect
    return inspect.isclass(task) and task() or task
class TaskType(type):
    def __new__(cls, clsname, clsbases, clsattrs):
        new = super(TaskType, cls).__new__

        task_name = clsattrs.get('name')
        if not task_name:
            clsattrs['name'] = task_name = gen_task_name()

        if task_name not in tasks:
            # For every Task, register one of it's instance
            tasks[task_name] = register(new(cls, clsname, clsbases, clsattrs))
        instance = tasks[task_name]
        return instance.__class__
@with_metaclass(TaskType)
class Task(object):
    def __call__(self, *args, **kwargs):
        self.run(*args, **kwargs)
    def run(self, *args, **kwargs):
        pass

class Task1(Task):
    def run(self, *args, **kwargs):
        print "this is task1"
print tasks

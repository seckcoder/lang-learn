from proj import tasks

# Callback
#res = tasks.add.apply_async((2, 2), link=tasks.add_callback.s())
#print res.get()

# Exc Callback
tasks.add_exc.apply_async((2, 0), link_error=tasks.add_exc_callback.s())

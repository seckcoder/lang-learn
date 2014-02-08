"""Demo for redis"""
import redis

def client_side_incr(pipe):
    """func to be executed in a transaction"""
    current_value = pipe.get("liwei")
    print current_value
    next_value = int(current_value) + 1
    pipe.multi()
    pipe.set("liwei", next_value)

def demo_transaction():
    """A common issue occurs when requiring atomic transactions but needing to
    retrieve values in Redis prior for use within the transaction. For
    instance, let's assume that the INCR command didn't exist and we need to
    build an atomic version of INCR in Python. The completely naive implementation
    could GET the value, increment it in Python, and SET the new value back.
    However, this is not atomic because multiple clients could be doing this
    at the same time, each getting the same value from GET. Enter the WATCH command.
    WATCH provides the ability to monitor one or more keys prior to starting a transaction.
    If any of those keys change prior the execution of that transaction,
    the entire transaction will be canceled and a WatchError will be raised."""
    client = redis.StrictRedis()
    client.set("liwei" ,23)
    with client.pipeline() as pipe:
        while 1:
            try:
                pipe.watch("liwei")
                # after WATCHNIG, pipeline is put into immediate execution
                # mode(and we can get the current value)
                # unitl we tell it to start buffering mode again(with multi).
                current_value = pipe.get("liwei")
                next_value = int(current_value) + 1
                pipe.multi()
                # we use multi to enter buffering model
                pipe.set("liwei", next_value)
                pipe.execute()
                break
            except redis.WatchError:
                # if another client changed the key: "liwei" between
                # the time we started WATCHING it and the pipeline's execution,
                # an exception will happend. What we can do now is to just retry.
                continue
    print client.get("liwei")


    # an easier way to use transaction is through `transaction`
    client.transaction(
        # specify the func to be executed in a transaction
        client_side_incr,
        # specify watched keys
        "liwei")
    print client.get("liwei")

demo_transaction()

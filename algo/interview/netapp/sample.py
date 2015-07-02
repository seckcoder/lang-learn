"""
Sample of Problem 1
"""

from core import Query, QueryError


try:
    q = Query([{
        "id":1,
        "fn":'sam',
        'ln':'anderson',
        'subjects':['physics', 'math', 'politics']
        },{
        "id":2,
        "fn":"liu",
        "ln":"liu",
        "subjects":["math","chemistry","literature"]
        },{
        "id":"3ag",
        "fn":"Srinivasa",
        "ln":"venkata subramaniam sambashivam",
        "subjects":["math","computer science"]
        },{
        "id":"4",
        "fn":"segun",
        "ln":"ode'kle",
        "subjects":["literature","environment science"]
        }])
    query1 = {
            "and": [{
                "or":[{
                    "fn":"liu"
                }, {
                    "ln":"anderson"
                }]
            }, {
                "subjects":{
                    "has":["physics"]
                 }
            }]
        }
    query2 = {
        "or":[{
            "fn":"liu"
         }, {
             "ln":"anderson"
         }]
    }
    print q.Q(query1)
except QueryError as e:
    print e

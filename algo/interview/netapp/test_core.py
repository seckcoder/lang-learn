"""
Unittest of core.py(Problem 1)

"""

import unittest
from core import Query

class TestCore(unittest.TestCase):
    def setUp(self):
        data = [{
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
        }]
        self.q = Query(data)

    def test_select_id_exist(self):
        query = { 'id':1 }
        self.assertEqual(self.q.select(query)[0]["id"], 1)

    def test_select_id_not_exist(self):
        query = { 'id' : 5}
        self.assertEqual(self.q.select(query), [])
    
    def test_select_fn_exist(self):
        query = { 'fn' : 'segun' }
        self.assertEqual(self.q.select(query)[0]['fn'], 'segun')
    
    def test_select_fn_not_exist(self):
        query = { 'fn' : 'Tongtong'}
        self.assertEqual(self.q.select(query), [])

    def test_select_ln_exist(self):
        query = { 'ln': "anderson" }
        self.assertEqual(self.q.select(query)[0]['ln'], 'anderson')

    def test_select_ln_not_exist(self):
        query = { 'ln': 'Bao' }
        self.assertEqual(self.q.select(query), [])

    def test_select_subjects_equal(self):
        query = { 'subjects': {
            "=": ["math","chemistry","literature"]
            }
            }
        self.assertEqual(self.q.select(query)[0]["id"], 2)

    def test_select_subjects_oneof(self):
        query = { "subjects": {
            "oneof": ["literature","environment science", "math"]
            }}
        self.assertEqual(self.q.select(query)[0]["id"],
            '4')

    def test_select_subjects_has(self):
        query = { "subjects": {
            "has": ["math"]
            }}
        self.assertEqual(len(self.q.select(query)), 3)

    def test_select_or(self):
        query = {
        "or":[{
            "fn":"liu"
         }, {
             "ln":"anderson"
         }]
        }
        self.assertEqual(len(self.q.select(query)),2)

    def test_select_and(self):
        query = {
        "and":[{
            "fn": "liu"
            }, {
            "subjects": {
                "has": ["math"]
            }
            }]
        }
        self.assertEqual(self.q.select(query)[0]['fn'], "liu")

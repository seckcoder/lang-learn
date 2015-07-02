'''
Problem-1:
    This is a really interesting problem. I think there are at least three methods to solve it.

    1. Develop a dsl for query string. We can use SQL style grammar, develop a parser for it and interpret/compile, evaluate it during the query.
    
    2. Inspired by LINQ, we can do similar things there.

    However, 1 and 2 are overskill for this interview problem, although they are both great design choices
    for realworld development.

    My choice here is use Python dict data to explicitly represent the DSL ast tree, so we have no need to parse it.

'''


class QueryError(Exception):
    pass

class Query(object):
    def __init__(self, data):
        self.data = data

    def select(self, query):
        # TODO: additional error checking
        return self._select(query)
    
    def _select(self, query):
        if query.has_key('and'):
            return self._select_and(query['and'])
        elif query.has_key('or'):
            return self._select_or(query['or'])
        elif query.has_key('id'):
            return self._select_id(query['id'])
        elif query.has_key('fn'):
            return self._select_fn(query['fn'])
        elif query.has_key('ln'):
            return self._select_ln(query['ln'])
        elif query.has_key('subjects'):
            return self._select_subjects(query['subjects'])
        else:
            raise QueryError("Unrecognized query %s" % query)

    def _select_id(self, id):
        items = []
        for item in self.data:
            if item['id'] == id:
                items.append(item)
                break
        return items

    def _items_to_dict(self, items):
        dict_items = {}
        for item in items:
            dict_items[item['id']] = item
        return dict_items
    
    def _dict_intersect(self, dict1, dict2):
        new_dict = {}
        for id,item in dict1.iteritems():
            if dict2.has_key(id):
                new_dict[id] = item
        return new_dict

    # This function conducts a side-effect update on dict2
    def _dict_union(self, dict1, dict2):
        new_dict = {}
        for id,item in dict1.iteritems():
            new_dict[id] = item

        for id,item in dict2.iteritems():
            new_dict[id] = item

        return new_dict

    def _select_and(self, queries):
        if not queries:
            return []
        
        final_items = self._items_to_dict(
                self._select(queries[0]))

        for query in queries[1:]:
            cur_items = self._items_to_dict(
                    self._select(query))
            final_items = self._dict_intersect(cur_items, final_items)

        return final_items.values()
    
    def _select_or(self, queries):
        if not queries:
            return []
        
        final_items = self._items_to_dict(
                self._select(queries[0]))
        
        for query in queries[1:]:
            cur_items = self._items_to_dict(
                    self._select(query))
            final_items = self._dict_union(cur_items, final_items)

        return final_items.values()

    def _select_fn(self, fn):
        return [item for item in self.data if item['fn'] == fn]

    def _select_ln(self, ln):
        return [item for item in self.data if item['ln'] == ln]

    def _select_subjects(self, query):
        if query.has_key('='):
            return self._select_subjects_equal(query['='])
        elif query.has_key('has'):
            return self._select_subjects_has(query['has'])
        elif query.has_key('oneof'):
            return self._select_subjects_oneof(query['oneof'])
        else:
            raise QueryError("Unknown subjects query: %s" % query)


    def _select_subjects_equal(self, subjects):
        sorted_subjects = sorted(subjects)
        return [item for item in self.data if sorted(item["subjects"]) == sorted_subjects]


    def _select_subjects_has(self, subjects):
        subjects = set(subjects)

        return [item for item in self.data \
                if subjects.issubset(set(item["subjects"]))]

    # The one of definition here is a little confusing.
    # I assume that oneof here means there at least one subject and all of them are
    # members of queried subjects
    def _select_subjects_oneof(self, subjects):
        subjects = set(subjects)
        items = []
        for item in self.data:
            set_subjects = set(item["subjects"])
            if set_subjects and set_subjects.issubset(subjects):
                items.append(item)

        return items

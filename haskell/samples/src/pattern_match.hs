

bar = len [1,2,3]
  where len [] = 0
        len (x:xs) = 1 + len xs

foo = fact 10
  where fact 0 = 1
        fact 1 = 1
        fact n = n * (fact (n-1))


reqs = client 0 resps

resps = server reqs

client init ~(resp:resps) = init : client (next resp) resps
server (req:reqs) = process req : server reqs

next resp = resp
process req = req+1


main = print $ take 10 reqs

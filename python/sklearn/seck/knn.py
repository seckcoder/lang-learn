from sklearn.neighbors import NearestNeighbors
import numpy as np

samples = [[0, 0, 2], [1, 0, 0], [0, 0, 1]]

neigh = NearestNeighbors(2, 0.4)

neigh.fit(samples)

dist, neighbors = neigh.kneighbors(samples, return_distance=True)
print dist
print neighbors

print np.max(dist, axis=1)

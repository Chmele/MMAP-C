import itertools
pows = itertools.count(0, 5)
sizes = (2**power for power in itertools.islice(pows, 7))

for size in sizes:
    with open(f'files/file{size}', "wb") as iowrapper:
        iowrapper.truncate(size)

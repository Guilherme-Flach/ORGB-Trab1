# -*- coding: utf-8 -*-
######################################################################
## Classes relacionadas às caches. Podem ser modificadas para alterar
## o tamanho (size), a associatividade (assoc), a latência no caso de
## hit (hit_latency) e a latência no caso de miss (response_latency) -
## ou seja, o tempo necessário para encaminhar a requisição ao proximo
## nível na hierarquia.
######################################################################

from m5.objects import Cache

class BasicL1ICache(Cache):

    size = '64kB' # increased from 32kB to 64kB
    assoc = 16 # increased from 8 to 16
    tag_latency = 1
    data_latency = 1
    response_latency = 1
    mshrs = 4
    tgts_per_mshr = 16

    def __init__(self, options=None):
        super(BasicL1ICache, self).__init__()        
        pass

class BasicL1DCache(Cache):

    size = '64kB' # increased from 32kB to 64kB
    assoc = 16 # increased from 8 to 16
    tag_latency = 1
    data_latency = 2
    response_latency = 2
    mshrs = 4
    tgts_per_mshr = 16

    def __init__(self, latency):
        super(BasicL1DCache, self).__init__()
        
        self.data_latency = latency
        pass

class BasicL2Cache(Cache):

    size = '512kB' # increased from 256kB to 512kB
    assoc = 16  # increased from 8 to 16
    tag_latency = 8
    data_latency = 12
    response_latency = 4
    mshrs = 16
    tgts_per_mshr = 16

    def __init__(self, options=None):
        super(BasicL2Cache, self).__init__()
        pass


class BasicL3Cache(Cache):

    size = '4MB' # increased from 2MB to 4MB
    assoc = 16
    tag_latency = 12
    data_latency = 36
    response_latency = 4
    mshrs = 16
    tgts_per_mshr = 16

    def __init__(self, options=None):
        super(BasicL3Cache, self).__init__()
        pass
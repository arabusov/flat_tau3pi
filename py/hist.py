#!/usr/bin/python
from ROOT import TH1D
import sys

data=[]
fl=open (sys.argv[1])
h=TH1D  ("hist", "Histogram",100,0.,3.)
for line in fl:
  h.Fill (float(line))
h.Draw()
raw_input()

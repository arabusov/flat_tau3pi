#!/usr/bin/python
from ROOT import TH2D
import sys

data=[]
fl=open (sys.argv[1])
h=TH2D  ("hist", "Histogram",500,0.,3.,500,0,3.)
for line in fl:
  h.Fill (
  float(line.split()[int(sys.argv[2])]),
  float(line.split()[int(sys.argv[3])]))
h.Draw("colz")
raw_input()

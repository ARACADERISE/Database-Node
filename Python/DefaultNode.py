import os, json

"""
	Touches up on files containing data about the Default  Database Node(DefaultNodeSetup).
	This goes strictly off of data stored in CreatedDefaultNode.
	Kind of useless, but it is way better than having to write a new function in types.h and CORE.c
"""

if os.path.exists('CreateDefaultNode'):
	data = open('CreateDefaultNode','r').read()

data = data.replace('\n','')

if 'Default Database Node created successfully' in data:
	DefaultDbName = "DefaultNodeSetup"
	Msg = 'Default Database Node created successfully'
	data = data.replace('Default Database Node created successfully','')

DefaultDbId = data

data = '[%s]\n\t\t!ID!\t~\t%s\n\t\t!NOTE!\t~\t%s'

with open('CreatedDefaultNode','w') as file:
	file.write(data % (DefaultDbName,DefaultDbId,Msg))
	file.flush()
	file.close()

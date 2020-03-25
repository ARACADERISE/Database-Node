import os, json

# will be used later on when bigger files are generated
try:
	from tqdm import tqdm
except ImportError:
	os.system('pip install tqdm')
	from tqdm import tqdm

"""
	Opens the files storing information about the Database Nodes being added,
	and takes the data and puts it into a .json formatted file
"""

listed_ = []
node_names = []
Action = []
IdNumber = []
d = 1
nums = ['1','2','3','4','5','6','7','8','9','0']
ADDINFO = ''
DATA = []
AllAddedFiles = []
FoundFiles = []

for i in os.listdir(os.path.abspath('.')):
	if 'Node Information #' in i:
		listed_.append(i)

if len(listed_) != 0:
	for i in range(len(listed_)):
		data = open(listed_[i],'r').read()
		node_names.append(data)

	dirs = [os.listdir(os.path.abspath('.'))]

	for i in range(len(node_names)):
		if str(d) in node_names[i]:
			TOTAL_LENGTH = len(node_names[i])
			index = node_names[i].find(str(d))
			
		
		IdNumber.append(node_names[i][index])
		node_names[i] = node_names[i].replace('\n','')
		node_names[i] = node_names[i].replace(IdNumber[i],'')
		for n in nums:
			if n in node_names[i]:
				ind = node_names[i].find(n)
				node_names[i] = node_names[i].replace(node_names[i][ind],'')
				IdNumber[i]+=n
				if '12' in IdNumber:
					IIndex = IdNumber.index('10')
					IdNumber[IIndex+1]='11'
		Action.append(node_names[i])
		node_names[i] = node_names[i].replace('Added Database Node ','')
		if node_names[i] == 'DefaultNodeSetup':
			node_names[i] = {'Default Node(NEEDED)':node_names[i]}
		if 'DefaultNodeSetup' in Action[i]:
			Action[i] = {'Default Node Added:':Action[i]}
		
		AllAddedFiles.append(listed_[i].replace(' ',''))
		data_ = {'Actions':Action,'NodeNames':node_names,'NodeIds':IdNumber,'DataFiles':AllAddedFiles}

		ADDINFO = '[AddedDatabaseNode]\n\t\t!Node name!\t~\t%s\n\t\t!Node Id!\t~\t%s'
		DATA.append(ADDINFO % (node_names[i],IdNumber[i]))

		d+= 1
	
	# If the user deletes the Database Nodes, this will update the files
	for i in range(len(dirs[0])):
		if 'NodeInformation#' in dirs[0][i]:
			FoundFiles.append(dirs[0][i])
	for i in FoundFiles:
		if i in AllAddedFiles:
			pass
		if not i in AllAddedFiles:
			os.remove(i)

	with open('NodeData.json','w') as NodeData:
		NodeData.write(json.dumps(
			data_,
			indent=2,
			sort_keys=False
		))
		NodeData.flush()
		NodeData.close()

	for i in range(len(listed_)):
		os.remove(listed_[i])
	
	for i in range(len(listed_)):
		listed_[i] = listed_[i].replace(' ','')

		with open(listed_[i],'w') as UpdFile:
			UpdFile.write(DATA[i])
			UpdFile.flush()
			UpdFile.close()
		
		DataOfFile = open(listed_[i],'r').read()
		if 'DefaultNodeSetup' in DataOfFile:
			new = '[DefaultNodeMsg]\n\t\tMESSAGE\t~\tREFER TO THE CreateDefaultNode FILE'
		
			with open(listed_[i],'w') as Update:
				Update.write(new)
				Update.flush()
				Update.close()

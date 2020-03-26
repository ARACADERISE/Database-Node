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

# For the Nodes
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
dirs = [os.listdir(os.path.abspath('.'))]

# For the Eras
era_types = ['wro','ro','wo','da'] # this is needed so we can parse through the files
listed__ = []
era_data = []
era = []
era_one = ''
AddedFiles = []
files = []

for i in os.listdir(os.path.abspath('.')):
	# This will parse files made for setting up the Database Nodes
	if 'Node Information #' in i:
		listed_.append(i)
	
	# This will parse files made for setting up the Era
	if 'Era Setup #' in i:
		listed__.append(i)

if len(listed__) != 0:
	for i in range(len(listed__)):
		open_ = open(listed__[i],'r').read()
		era_data.append(open_)
	
	for i in range(len(era_data)):
		if era_data[i][0] != 'w':
			for x in era_types:
				if x in era_data[i]:
					era.append(x)
		else:
			era.append('wro')

		era_data[i] = era_data[i].replace(era[i],'')
		era_data[i] = era_data[i].replace('\n','')
	
	if len(era_data) > 1:
		MoreThanOnce = False # False by defult
		for i in range(len(era_data)):
			if era_data[i] == era_data[i+1]:
				MoreThanOnce = True
			if MoreThanOnce:
				del(era_data[i+1])
				del(era[i+1])
				break
	
	data = {'Era Types':era,'Era Used For':era_data}
	
	with open('EraData.json','w') as EraSetup:
		EraSetup.write(json.dumps(
			data,
			indent=2,
			sort_keys=False
		))
		EraSetup.flush()
		EraSetup.close()

	for i in dirs[0]:
		if 'Era Setup #' in i:
			files.append(i)
			AddedFiles.append(i.replace(' ',''))

	write_ = '[EraSetupInformation]\n\t\t!Era Name!\t~\t%s\n\t\t!Action!\t~\t%s'

	for i in range(len(AddedFiles)):
		with open(AddedFiles[i],'w') as AddedFile:
			AddedFile.write(write_ % (era[i] if len(era) > 1 else era[0], era_data[i] if len(era_data) > 1 else era_data[0]))
			AddedFile.flush()
			AddedFile.close()

	for i in files:
		os.remove(i);

if len(listed_) != 0:
	for i in range(len(listed_)):
		data = open(listed_[i],'r').read()
		node_names.append(data)

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
	
	for i in AllAddedFiles:
		#listed_[i] = listed_[i].replace(' ','')

		for b in range(len(DATA)):
			with open(i,'w') as UpdFile:
				UpdFile.write(DATA[b])
				UpdFile.flush()
				UpdFile.close()
		
		DataOfFile = open(i,'r').read()
		if 'DefaultNodeSetup' in DataOfFile:
			new = '[DefaultNodeMsg]\n\t\tMESSAGE\t~\tREFER TO THE CreateDefaultNode FILE'
		
			with open(i,'w') as Update:
				Update.write(new)
				Update.flush()
				Update.close()


# should we give the script the ability to parse the dissasembly 
# from dasm or the spike log parser ? 

import os
import matplotlib.pyplot as plt 
import sys #for command line 
import pandas as pd



# list of instructions types including pseudo codes 

# Integer computation with some other insn
intcom  = { 'sext.w','addiw','addw','not','xori','seqz','sltiu' ,'sraiw','slliw','srli','mv','add','sub',
            'and','or','xor','sll','srliw','slli','sra','srai','srl', 'srli', 'lui', 'auipc','slt','addi','andi',
            'subw', 'slti','ori','nop' , 'c.nop' , 'c.addi' , 'c.addi4spn','c.addi16sp','c.mv','c.addiw','c.lui','c.bnez'}
# load & store 
loads   = {'li','lb','lh','ld','lw','sb','sh','sw','sd','lbu','lhu','c.ldsp','lwu','c.li','lw','c.sdsp'}

# control
control = {'jar','beqz','jr','beq','bne','bge','bgez','blt','bltz','bgeu','bltu','j','jr','c.j','dret','jal','jalr','ret','bnez','c.bnze'}

# custom 
ldpc    = {'ld.subsat','ld.abs','ld.max','ld.min','ld.eval','ld.rsign','ld.nmess','ld.addsat'}

csr     = {'csrr', 'csrs', 'csrw'}
sync    = {'fence'}
rvm     = {'divu','remu','divuw'}
rvf     = {'fmv.w.x'}

dir_path = os.path.dirname(os.path.realpath(__file__))+'/'

# return filename only 
def path_leaf(path):
    head, tail = os.path.split(path)
    return tail or os.path.basename(head)

# returns the instruction type 
def insn_group(insn):
    if insn in intcom:
        return "intcom"  
    elif insn in loads :
        return "loads"          
    elif insn in control :
        return "control"          
    elif insn in ldpc :
        return "ldpc"
    elif insn in csr:
        return 'csr'
    elif insn in sync:
        return 'sync'
    elif insn in rvm:
        return 'rvm'
    elif insn in rvf:
        return 'rvf'

# returns the % rounded to 2 decimals 
def get_perc(sum, val):
    return ((1 -(( sum - val )  / sum ))*100).round(2)

# expect full file path 
# returns df 
# optional : 
#   perc['none'|'yes'] : display percentage in a column 
#   write_file['none'|'yes'] : write in file  

def ftoDf(file, perc='none', write_file='none'):

    # get the filename w/o any type
    fname = (path_leaf(file).split('.'))[0]

    ls_test=[]
    stats=[]
    # read then quit 
    file2 = open(file,'r') 
    data  = file2.read()
    file2.close()

    data  = data.split('\n')
    for i in data:
        if i not in ls_test:
            ls_test.append(i)

    # goes throught the list of identified instructions
    for insn in ls_test :    
        insn_struct = { 
        'insn' : insn ,
        'type': insn_group(insn),
        'nb' : data.count(insn)}
        stats.append(insn_struct)
        
    df = pd.DataFrame(stats)
    df = df.sort_values('nb')

    if perc=='yes':
        df['perc']=0
        for idx in df.index:
            dta = get_perc(df.nb.sum(), df.nb.loc[idx])
            df.at[idx,'perc'] = dta

        # keeping columns names makes it complicated to work with 
        df=df.rename(columns={ 'nb':fname+'_nb' , 'perc':fname+'_perc' })

    else: 
        df=df.rename(columns={ 'nb':fname+'_nb'})

    if write_file=='yes':
        fRes = open(file + '.md','w') 
        fRes.write(file)
        fRes.write('\n\n' +df.to_markdown())
        fRes.write('\n\n' + S.to_markdown())
        fRes.write('\n\n'+ df.to_markdown(tablefmt='plain',index=False))
        fRes.close()
    
    return (df)

# not efficient 
def DftoS(df):
    S = df.groupby(['type']).sum()
    S = S.drop(['insn'],axis=1)
    return S


# empty dataframes
dfs = []
st=[]
eccList=[]
for idx, arg in enumerate(sys.argv[1:]):
    eccList.append(arg)


# working with ldpccst , ldpc , polar, polar_fsc
ecc     = ['ldpccst.out', 'ldpc.out' , 'polar.out','polar_fsc.out','turbo.out', 'dhrystone.out']

# we want these dynamicaly constructed with the inputs 
# list comphrension is used to work on a set of Dataframes

# from cli ? 
if(len(sys.argv)>1):
    for codes in eccList:
        dfs.append( ftoDf(dir_path+codes,perc='yes') )
else:
    dfs.append( ftoDf(dir_path+codes) )

st = [ DftoS(df) for df in dfs ]
stest = (st[0].join(st[1:])).fillna(0)

dfs     = [df.set_index('insn') for df in dfs]
# keep df0 since it contains list of instructions types (and cst)
dfs[1:] = [df.drop('type',axis=1) for df in dfs[1:]] 
dftest  = dfs[0].join(dfs[1:]).fillna(0)

# sort with the highest cycles count 
Smax = dftest.sum(numeric_only=True)
dftest = dftest.sort_values(Smax.idxmax())


###### PLOTTING 
# ploting subsequently is better ? 
fig, axs = plt.subplots(nrows=1 , ncols=2)

dftest.plot(kind = 'bar',xlabel="Insn type",ylabel="Nb")

bx= stest.data_nb.plot( kind = 'bar',
                xlabel="Insn type",ylabel="Nb",rot=45,
                 ax=axs[0])

Tstest = stest.drop(['data_perc'],axis=1).T
cx = Tstest.plot.bar(stacked=True, ax=axs[1])
print(dftest)
print(stest)
print(Tstest)

plt.show()



source('utils.r')
source('evaluation.r')

mainFolder     = '/home/felipelageduarte/survey/'
dataFolder     = sprintf('%s/data', mainFolder)
resultFolder   = sprintf('%s/pipeline', mainFolder)
testResult     = sprintf('%s/testResult', mainFolder)

pipelineEvaluate(dir = resultFolder, tech_name = 'emdmi', result_file=sprintf('%s/%s', testResult, 'emdmi.csv'))

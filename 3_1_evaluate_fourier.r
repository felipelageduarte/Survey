source('utils.r')
source('evaluation.r')

mainFolder     = '.'
dataFolder     = sprintf('%s/data', mainFolder)
resultFolder   = sprintf('%s/pipeline', mainFolder)
testResult     = sprintf('%s/testResult', mainFolder)

pipelineEvaluate(dir = resultFolder, tech_name = 'fourier', result_file=sprintf('%s/%s', testResult, 'fourier.csv'))

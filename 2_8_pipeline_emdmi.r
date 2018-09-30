source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

runPipeline(seriesList, emdmiDec, NULL, pipelineFolder, 'emdmi')

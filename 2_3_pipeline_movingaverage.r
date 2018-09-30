source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

params = expand.grid(order = 2:100, stringsAsFactors = FALSE)
runPipeline(seriesList, movingAverageSmoothingDec, params, pipelineFolder, 'movingAverageSmoothing')

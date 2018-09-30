source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

params   = expand.grid(cutoff = 1:500, stringsAsFactors = FALSE)
runPipeline(seriesList, fourierDec, params, pipelineFolder, 'fourier')

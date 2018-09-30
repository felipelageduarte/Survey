source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

params = expand.grid(r = seq(0.01, 0.5, by=0.05),
                     i = 1:4,
                     m = seriesList[[1]]$det.embDim,
                     d = seriesList[[1]]$det.sepDim
                    )
runPipeline(seriesList, lazyDec, params, pipelineFolder, 'lazy')

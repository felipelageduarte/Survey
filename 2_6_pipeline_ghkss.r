source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

params = expand.grid(q = 1:3,
                     k = 6:12,
                     r = seq(0.001, 0.01, by=0.0025),
                     i = 1:5,
                     m = seriesList[[1]]$det.embDim,
                     d = seriesList[[1]]$det.sepDim
                    )

runPipeline(seriesList, ghkssDec, params, pipelineFolder, 'ghkss')

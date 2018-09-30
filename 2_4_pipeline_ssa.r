source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

params = expand.grid(
  L = 130:180,
  neig = 1:2
)
runPipeline(seriesList, ssaDec, params, pipelineFolder, 'ssa', run_r = TRUE)

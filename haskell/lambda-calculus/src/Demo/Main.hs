
-- import Demo.StateT (demos)
import Demo.ReaderT1 (demos)
-- import Demo.ExceptT (demos)
-- import Demo.ContT (demos)

runDemo demos = print demos


main = runDemo demos

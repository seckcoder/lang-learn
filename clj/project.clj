(defproject clj "0.1.0-SNAPSHOT"
  :description "FIXME: write description"
  :url "http://example.com/FIXME"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :dependencies [[org.clojure/clojure "1.6.0"]
                 [org.clojure/tools.nrepl "0.2.5"]
                 [lein-light-nrepl "0.0.19"]
                 [org.clojure/core.typed "0.2.72"]
                 [org.clojure/core.match "0.2.1"]]
  :main ^:skip-aot clj.core
  :target-path "target/%s"
  :repl-options {:nrepl-middleware [lighttable.nrepl.handler/lighttable-ops]}
  :plugins [[lein-typed "0.3.5"]]
  :profiles {:uberjar {:aot :all}})

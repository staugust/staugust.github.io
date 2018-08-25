# Elasticsearch Concepts


## index.number_of_replicas
Since Elasticsearch 5.0, index level settings cannot be configured in elasticsearch.yml. 

With command below, you can reset **index.number_of_replicas** for index `skydiscovery-spark-1535006482290-36-6c375150f2973783a85bb6aed6bceea1-driver`

```
curl -X PUT "12.96.0.24:9200/skydiscovery-spark-1535006482290-36-6c375150f2973783a85bb6aed6bceea1-driver/_settings" -H 'Content-Type: application/json' -d'
{
    "index.number_of_replicas": 0
}
'
```

Or you can reset all existing indices' **index.number_of_replicas**.
```
curl -X PUT "12.96.0.24:9200/*/_settings" -H 'Content-Type: application/json' -d'
{
    "index.number_of_replicas": 0
}
'
```
Then you can set template for new created indices.
```
curl -X PUT "12.96.0.24:9200/_template/template_1" -H 'Content-Type: application/json' -d'
{
  "index_patterns": ["skydiscovery-*"],
  "settings": {
    "number_of_replicas": 0
  }
}
'
```

## Some other useful commands

```
curl -X GET "12.96.0.24:9200/_cluster/stats?human&pretty"
curl -X GET "12.96.0.24:9200/_cluster/health?human&pretty"


curl -XGET 172.16.160.46:9200/_cat/shards?h=index,shard,prirep,state,unassigned.reason| grep UNASSIGNED

curl -XGET 12.96.0.24:9200/_cat/shards?h=index,shard,prirep,state,unassigned.reason

curl -X PUT "12.96.0.24:9200/skydiscovery-spark-1535006482290-36-6c375150f2973783a85bb6aed6bceea1-driver/_settings" -H 'Content-Type: application/json' -d'
{
    "index.number_of_replicas": 0
}
'

curl "12.96.0.24:9200/_cat/shards?index=skydiscovery-jupyter-1534335684971-23-5d578d5cf6-zgzwg&v"

curl -X GET "12.96.0.24:9200/_cat/pending_tasks?v"

curl -X GET "12.96.0.24:9200/_cat/indices/skydiscovery-*?v&s=index"

curl -X GET "12.96.0.24:9200/skydiscovery-jupyter-1535002280447-34-779f99df9d-5mwdq/_settings?pretty"


curl -X PUT "12.96.0.24:9200/_template/template_1" -H 'Content-Type: application/json' -d'
{
  "index_patterns": ["skydiscovery-*"],
  "settings": {
    "number_of_replicas": 0
  }
}
'
curl -X GET "12.96.0.24:9200/_cat/indices?v&h=i,tm&s=tm:desc"
curl -X GET "12.96.0.24:9200/_segments?pretty"

curl -X GET "12.96.0.24:9200/skydiscovery-jupyter-1535103708113-79-7b85b88dc8-dng7q/_settings?pretty"


curl -X GET "localhost:9200/skydiscovery-ambassador-59cb5ccd89-5dhhv/_search?pretty" -H 'Content-Type: application/json' -d'
{
  "query": {
    "match_phrase": {
      "kubernetes.pod_name": "ambassador-59cb5ccd89-5dhhv"  
    }
  }
}'



```
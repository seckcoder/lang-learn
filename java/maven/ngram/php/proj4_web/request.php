<?php
if ( !isset($_REQUEST['term']) )
{       echo 'error';
        exit;
}

include('./httpful.phar');

// EDIT these to match your schema
$tableName="wp";
$columnFamily="wordpairs";

// trim leading and trailing spaces
$searchTerm = strtolower(trim( $_REQUEST['term'] ));

// Connect to HBASE server
//  note: we are running in non "security" mode, so no user auth needed
$url = "http://localhost:8080/".$tableName."/".urlencode($searchTerm);

//Send Request
$response = \Httpful\Request::get($url)->addHeader('Accept','application/json')->send();

//DEBUG
//echo $response;

// iterate through response, adding each to array
$data = array();
$json = json_decode($response,true);
$row=$json["Row"];
$Cell=$row["Cell"];

foreach($Cell as $item) {

    //DEBUG
    //echo $cell;

    $word = str_replace("$columnFamily:","",base64_decode($item["@column"]));

    //DEBUG - Adding word probablility
    //echo $word;
    //$probability = base64_decode($item['$']);

    $data[] = array(
					'label' => $word,//.", Prob:".$probability,
                    'value' => $searchTerm." ".$word
    );
}

// return JSON encoded array to the JQuery autocomplete function
echo json_encode($data);
flush();
?>


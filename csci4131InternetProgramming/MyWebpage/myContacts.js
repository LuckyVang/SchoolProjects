function changeEnlargedImage(imgPath) {
    if (typeof imgPath === 'string') {
        document.getElementById("enlargedImage").src=imgPath;
    }
}   


// GOOGLE API
var contactMarkers = [];
var searchMarkers = [];
var map;
let startLat;
let startLong;

function calcDistanceHover(idx) {
    startLat = contactMarkers[idx].position.lat();
    startLong = contactMarkers[idx].position.lng();
    calcDistance();
}

function calcDistance() {
    let targetLat = $("#targetLat").html();
    let targetLong = $("#targetLong").html();
    let targetDistanceValue = $("#targetDistanceValue");
    
    // obtained from https://www.movable-type.co.uk/scripts/latlong.html
    const R = 6371e3; // metres
    const startLatRadians = startLat * Math.PI/180; // φ, λ in radians
    const targetLatRadians = targetLat * Math.PI/180;
    const latDiff = (targetLat-startLat) * Math.PI/180;
    const longDiff = (targetLong-startLong) * Math.PI/180;

    const a = Math.sin(latDiff/2) * Math.sin(latDiff/2) +
            Math.cos(startLatRadians) * Math.cos(targetLatRadians) *
            Math.sin(longDiff/2) * Math.sin(longDiff/2);
    const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

    const d = R * c; // in metres
    // end obtained from https://www.movable-type.co.uk/scripts/latlong.html

    targetDistanceValue.html(d);
}


function initMap() {
    map = new google.maps.Map(document.getElementById("map"), {
      center: { lat: 44.9727, lng: -93.23540000000003 },
      zoom: 14,
    });

    addContactLocations(map);
}

function createMarker(place) {
    var marker = new google.maps.Marker({
        position: place.geometry.location,
        map: map
    });
    return marker;
}

function addContactLocations(map) {
    var contactLocations = document.getElementsByClassName("contactLocation");
    var contactInfos = document.querySelectorAll('.contactInfo td');
    var request;
    var service = new google.maps.places.PlacesService(map);

    for (let i = 0; i < contactLocations.length; i++) {
        request = {
            query: contactLocations[i].textContent,
            fields: ['name', 'geometry'],
        };
        
        service.findPlaceFromQuery(request, function(results, status) {
            if (status === google.maps.places.PlacesServiceStatus.OK) {
                contactMarkers.push(createMarker(results[0])); 
                let makersLength = contactMarkers.length - 1;
                google.maps.event.addListener(contactMarkers[makersLength], "click", function() {
                    let contentString = 
                    '<div id="content">' +
                        '<div id="bodyContent">' +
                            contactInfos[i*6].textContent + '<br>' +  // gets name 
                            contactInfos[i*6 + 3].textContent + '<br>' +  // gets address
                            contactInfos[i*6 + 4].textContent + '<br>' +  // gets contact
                        '</div>' +
                    '</div>';
                    let infowindow = new google.maps.InfoWindow({content: contentString});		
                    infowindow.open(map, contactMarkers[makersLength]);
                });
                
              map.setCenter(results[0].geometry.location);
            }
        });
    }
}


function mapSearch() {
    // clear previous search markers if any
    for (let i = 0; i < searchMarkers.length; i++) {
        searchMarkers[i].setMap(null);
        searchMarkers[i] = null;
    }
    searchMarkers = [];
    directionsRenderer.setMap(null);  // clear previous routes if any

    
    $("#routeInstructions").css("width", "0%");
    $("#routeInstructions").css("margin-right", ".5%");
    $("#map").css("width", "65%");

    let searchOptions = $("#searchOptions").val();
    let otherSearchOptions = $("#otherSearchOptions").val();
    let searchRadius = $("#searchRadius").val();


    if (searchRadius == "") {
        searchRadius = "1609";
    } else {
        searchRadius = parseFloat(searchRadius) * 1609.34;
        searchRadius = "" + searchRadius;
    }

    let service = new google.maps.places.PlacesService(map);
    let request;
    let temp = new google.maps.LatLng(44.9727,-93.23540000000003);
    
    request = {
        location: temp,
        radius: searchRadius,
        type: searchOptions,
        keyword: otherSearchOptions,
      };
    
    service.nearbySearch(request, function(results, status) {
        if (status === google.maps.places.PlacesServiceStatus.OK) {
            for (let j = 0; j < results.length; j++) {
                searchMarkers.push(createMarker(results[j])); 
                let makersLength = searchMarkers.length - 1;
                google.maps.event.addListener(searchMarkers[makersLength], "click", function() {
                    let contentString = 
                    '<div id="content">' +
                        '<div id="bodyContent">' +
                            results[j].name + 
                        '</div>' +
                    '</div>';
                    let infowindow = new google.maps.InfoWindow({content: contentString});		
                    infowindow.open(map, searchMarkers[makersLength]);

                });
                map.setCenter(results[0].geometry.location);
            }
        }
    });
}

var directionsService = new google.maps.DirectionsService();
var directionsRenderer = new google.maps.DirectionsRenderer();
let travelMode = $("input[name='getDirectionsTransportationMode']:checked").val();
directionsRenderer.setMap(map);

function getDirectionsOnclick() {
    // change target coords when user selects someone from the getDirections drop down menu
    let targetLat = $("#targetLat");
    let targetLong = $("#targetLong");
    let targetName = $("#getDirectionsOptions").val();
    let contactInfos = document.querySelectorAll('.contactInfo td');
    travelMode = $("input[name='getDirectionsTransportationMode']:checked").val();
    // clear previous routes if any
    directionsRenderer.setMap(null);
    directionsRenderer.setMap(map);
    // clear search markers if any
    for (let i = 0; i < searchMarkers.length; i++) {
        searchMarkers[i].setMap(null);
        searchMarkers[i] = null;
    }
    searchMarkers = [];


    // find target coordinates
    for (let i = 0; i < contactInfos.length; i++) {
        if (targetName == contactInfos[i].textContent) {
            let x = Math.floor(i/6);
            console.log("x: " + x);
            targetLat.html(contactMarkers[x].position.lat());
            targetLong.html(contactMarkers[x].position.lng());
            break;
        }
    }
    
    // determine starting position (either current location or inputted value)
    let startingSpot = $("#getDirectionsStarting").val();
    // starting location is set to the inputted value
    if (startingSpot != "") {
        console.log("input value");
        let request;
        let service = new google.maps.places.PlacesService(map);

        request = {
            query: startingSpot,
            fields: ['name', 'geometry'],
        };
        
        service.findPlaceFromQuery(request, function(results, status) {
            if (status === google.maps.places.PlacesServiceStatus.OK) {
                startLat = results[0].geometry.location.lat();
                startLong = results[0].geometry.location.lng();
                map.setCenter(results[0].geometry.location);
                calcDistance();
                
                // display route from starting location to target location
                request = {
                    origin: new google.maps.LatLng(startLat, startLong),
                    destination: new google.maps.LatLng(targetLat.html(), targetLong.html()),
                    travelMode: travelMode
                };

                console.log("origin coords: " + startLat + ", " + startLong);
                console.log("destination coords: " + targetLat.html() + ", " + targetLong.html());
                console.log("travel mode: " + travelMode);
                directionsService.route(request, function(result, status) {
                    if (status == 'OK') {
                        console.log("okay status");
                        directionsRenderer.setDirections(result);

                        // display step by step instructions for the route
                        let instructions = result.routes[0].legs[0].steps;
                        let message = "";
                        for (let k = 0; k < instructions.length; k++) {
                            message += instructions[k].instructions + "<br>";
                        }

                        let routeInstructions = $("#routeInstructions");
                        routeInstructions.html(message);
                        routeInstructions.css("width", "15%");
                        routeInstructions.css("margin-right", ".5%");
                        $("#map").css("width", "49.5%");
                    }
                });
            }
        });
    } else {
        console.log("current location");
        // setarting location is the current location

        if (navigator.geolocation) {
            let nav = navigator.geolocation.getCurrentPosition(
                (position) => {
                    const pos = {
                    lat: position.coords.latitude,
                    lng: position.coords.longitude,
                    };
                    map.setCenter(pos);

                    // display route from starting location to target location
                    var request = {
                        origin: new google.maps.LatLng(pos.lat, pos.lng),
                        destination: new google.maps.LatLng(targetLat.html(), targetLong.html()),
                        travelMode: travelMode
                    };
                    // Joan Gabel: 44.9758905, -93.2346317

                    console.log("origin coords: " + pos.lat + ", " + pos.lng);
                    console.log("destination coords: " + targetLat.html() + ", " + targetLong.html());
                    console.log("travel mode: " + travelMode);
                    directionsService.route(request, function(result, status) {
                        if (status == 'OK') {
                            console.log("okay status");
                            directionsRenderer.setDirections(result);

                            // display step by step instructions for the route
                            let instructions = result.routes[0].legs[0].steps;
                            let message = "";
                            for (let k = 0; k < instructions.length; k++) {
                                message += instructions[k].instructions + "<br>";
                            }

                            let routeInstructions = $("#routeInstructions");
                            routeInstructions.html(message);
                            routeInstructions.css("width", "15%");
                            routeInstructions.css("margin-right", ".5%");
                            $("#map").css("width", "49.5%");
                        }
                    });
                },
                () => {
                    handleLocationError(true, infoWindow, map.getCenter());
                }
            );
        } else {
            // Browser doesn't support Geolocation
            handleLocationError(false, infoWindow, map.getCenter());
        } 
    }
}


$().ready(function() {
    // check if user selected "other" for search options
    $("#searchOptions").change(function() {
        if ($("#searchOptions").val() == "other") {
            $("#otherSearchOptions").prop("disabled", false);
        } else {
            $("#otherSearchOptions").prop("disabled", true);
        }
    })

    // find contact names and add values to the get direction options
    // let contactNames = document.querySelectorAll(".contactInfo td");
    // let myOptions = [];
    // for (let i = 0; i < contactNames.length / 6; i++) {
    //     myOptions.push(contactNames[i*6]);
    // }

    // $.each(myOptions, function(idx, val) {
    //     $('#getDirectionsOptions').append(new Option(val.textContent));
    // });

});

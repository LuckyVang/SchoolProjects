function formInputCheckValidity() {
    if (this.checkValidity()) {
        this.style.backgroundColor = "white";
    } else {
        this.style.backgroundColor = "#db4646";
    }
}

function formReset() {
    let formInputs = document.querySelectorAll("form input");
    for (let i=0; i<formInputs.length-2; i++) {
        formInputs[i].style.backgroundColor="white";
    }
}

let formInputs = document.querySelectorAll("form input");
for (let i=0; i<formInputs.length; i++) {
    formInputs[i].addEventListener("blur", formInputCheckValidity);
}

let map;

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
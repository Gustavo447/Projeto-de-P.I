let htmlDisplayed = false;

function isAutomatic(value) {
    if (value == 1) {
        if (htmlDisplayed) {
            // Remover os elementos HTML anteriores se já tiverem sido exibidos
            document.getElementById("options").innerHTML = "";
            htmlDisplayed = false;
        }
    } else {
        if (!htmlDisplayed) {
            var div = document.getElementById("options");

            // Criar elemento para a lâmpada
            var lampElement = document.createElement("div");
            lampElement.className = "card h-100 m-3";
            lampElement.innerHTML = "<div class='card-body text-center'> <h5 class='card-title mb-5'>Lâmpada</h5> <button onclick='releOff1()' class='btn btn-danger'>OFF</button> <button onclick='releOn1()' class='btn btn-success'>ON</button></div>";
            div.appendChild(lampElement);

            // Criar elemento para a ventoinha
            var fanElement = document.createElement("div");
            fanElement.className = "card h-100";
            fanElement.innerHTML = "<div class='card-body text-center'> <h5 class='card-title mb-5'>Ventoinha</h5> <button onclick='releOff2()' class='btn btn-danger me-2'>OFF</button><button onclick='releOn2()' class='btn btn-success'>ON</button> </div>";
            div.appendChild(fanElement);

            htmlDisplayed = true;
        }
    }
}



//function isAutomatic(value) {
    //if (value == 1) {

    //} else {

        //var div = document.getElementById("options");

        // Criar elemento para a lâmpada
        //var lampElement = document.createElement("div");
        //lampElement.className = "card h-100 m-3";
        //lampElement.innerHTML = "<div class='card-body text-center'> <h5 class='card-title mb-3'>Lâmpada</h5> <button onclick='releOff1()' class='btn btn-outline-danger'>OFF</button> <button onclick='releOn1()' class='btn btn-outline-success'>ON</button></div>";
        //div.appendChild(lampElement);

        // Criar elemento para a ventoinha
        //var fanElement = document.createElement("div");
        //fanElement.className = "card h-100 mt-3";
        //fanElement.innerHTML = "<div class='card-body text-center'> <h5 class='card-title mb-3'>Ventoinha</h5> <button onclick='releOff2()' class='btn btn-outline-danger'>OFF</button><button onclick='releOn2()' class='btn btn-outline-success'>ON</button> </div>";
        //div.appendChild(fanElement);
//    }
//}

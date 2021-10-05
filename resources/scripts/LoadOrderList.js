	function loadOrderTable(Responce)
	{
		var message = document.getElementById('Message');
		message.innerHTML = Responce.message;
	
		JsonTable = Responce.table;
		var table = document.getElementById('TableBlock');
		table.innerHTML = "";
		table.innerHTML += "<tr><td>work_type</td><td>order_date</td><td>deadline</td><td>executor</td><td>customer</td><td>status</td><td>place</td></tr>"
		for (i = 0; i < JsonTable.length; i++)
		{
			var tr = document.createElement("tr");
			var Row = JsonTable[i];
			
			tr.innerHTML += "<td><a href=\"/order/" + Row.id + "\">" + Row.work_type + "</a></td>";
			tr.innerHTML += "<td><a href=\"/order/" + Row.id + "\">" + Row.order_date + "</a></td>";
			tr.innerHTML += "<td><a href=\"/order/" + Row.id + "\">" + Row.deadline + "</a></td>";
			tr.innerHTML += "<td><a href=\"/order/" + Row.id + "\">" + Row.executor + "</a></td>";
			tr.innerHTML += "<td><a href=\"/order/" + Row.id + "\">" + Row.customer + "</a></td>";
			tr.innerHTML += "<td><a href=\"/order/" + Row.id + "\">" + Row.status + "</a></td>";
			tr.innerHTML += "<td><a href=\"/order/" + Row.id + "\">" + Row.place + "</a></td><br>";
			
			table.append(tr);
		}
	}
	function uploadTable()
	{
		var message = createMessage();
		var form = createMyForm(message);
		sendForm(form, loadOrderTable, window.location.pathname);
	}
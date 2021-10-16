	function loadOrderTable(Responce)
	{
		var message = document.getElementById('Message');
		if (Responce.message == undefined)
			message.hidden = true;
		else
		{
			message.hidden = false;
			message.innerHTML = Responce.message;
		}
	
		JsonTable = Responce.table;
		var table = document.getElementById('TableBlock');
		table.innerHTML = "";
		table.innerHTML += "<tr><td>Тип работ</td><td>Дата заявки</td><td>Дедлайн</td><td>Исполнитель</td><td>Заказчик</td><td>Статус</td><td>Место</td></tr>"
		for (i = 0; i < JsonTable.length; i++)
		{
			var tr = document.createElement("tr");
			var Row = JsonTable[i];
			tr.className  = "TableRow";
			tr.order = Row.id;
			tr.innerHTML += "<td class=\"TableCell\">" + Row.work_type + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.order_date + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.deadline + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.executor + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.customer + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.status + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.place + "</td>";
			
			table.append(tr);
			table.lastChild.addEventListener("click", function(){goToOrder(this)});
		}
	}
	function uploadTable()
	{
		var message = createMessage();
		var form = createMyForm(message);
		sendForm(form, loadOrderTable, window.location.pathname);
	}
	function goToOrder(e)
	{
		id = e.order;
		window.location.replace("/order/" + id);
	}
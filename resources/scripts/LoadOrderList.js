	function converStatus(i)
	{
		if (i = 0)
			return "Создана";
		if (i = 1)
			return "В поле";
		if (i = 2)
			return "Камеральная обработка";
		if (i = 3)
			return "Закрыта";

		return "Ошибка";
	}	

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
		table.innerHTML += "<tr><td>№</td><td>Срок выполнения</td><td>Место</td><td>Тип работ</td><td>Вид работ</td><td>Инженер</td><td>Полевик</td><td>Заказчик</td><td>Статус</td></tr>"
		for (i = 0; i < JsonTable.length; i++)
		{
			var tr = document.createElement("tr");
			var Row = JsonTable[i];
			tr.className  = "TableRow";
			tr.order = Row.id;
			tr.innerHTML += "<td class=\"TableCell\" width=\"60px\">" + Row.id + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.deadline + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.place + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.work_type + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.work_class + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.ingeneer + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.fielder + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" + Row.customer + "</td>";
			tr.innerHTML += "<td class=\"TableCell\">" +  converStatus(Row.status) + "</td>";
			
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
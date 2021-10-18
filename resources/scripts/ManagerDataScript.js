    Statuses.innerHTML = "<option value=\"0\">Создан</option>" +
						"<option value=\"3\">Закрыт</option>";
	
	function editData()
	{
		Statuses.disabled = false;
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
			if (Inputs[item].name != "executor")
				Inputs[item].readOnly = false;
		
		Buttons = ButtonBlock.querySelectorAll("input");
		for (item  = 0; item < Buttons.length; item++)
		{
			if (Buttons[item].value == "Изменить")
				Buttons[item].hidden = true;

			if (Buttons[item].value == "Отмена" || Buttons[item].value == "Сохранить")
				Buttons[item].hidden = false;		
		}
	}
	function cancelEdit()
	{
		Statuses.disabled = true;
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
			Inputs[item].readOnly = true;
		
		Buttons = ButtonBlock.querySelectorAll("input");
		for (item  = 0; item < Buttons.length; item++)
		{
			if (Buttons[item].value == "Изменить")
				Buttons[item].hidden = false;

			if (Buttons[item].value == "Отмена" || Buttons[item].value == "Сохранить")
				Buttons[item].hidden = true;
		}
	}
	
	function printData(Responce)
	{
		path = window.location.pathname;
		path = path.substr(path.lastIndexOf("/") + 1);
		if ("new" == path)
			Title.innerHTML = "Новый заказ";
		else
			Title.innerHTML = "Заказ номер " + path;
		
		if (Responce.message == undefined)
			Message.hidden = true;
		else
		{
			Message.hidden = false;
			Message.innerHTML = Responce.message;
		}
	
		Inputs = InputBlock.querySelectorAll("input");
		if (Responce.table == undefined)
			return;
		
		JsonTable = Responce.table[0];
		for (i = 0; i < Inputs.length; i++)
		{
			Inputs[i].value = JsonTable[Inputs[i].name];
		}
	}
	
	function loadDoc()
	{
		var FileName = DocList.value;
		var url = "/document/" + FileName + "?";
		var Args = createMessage();
		for (i = 0; i < Args.length; i++)
		{
			if (i > 0)
				url += "&";
			url += Args[i].name + "=" + Args[i].value;
		}
		window.open(url);
	}
	
	function makeFileList(Responce)
	{
		path = window.location.pathname;
		path = path.substr(path.lastIndexOf("/") + 1);
		if ("new" == path || Responce.length == 0)
		{
			DocList.hidden = "true";
			LoadDoc.hidden = "true";
			return ;
		}
			
		DocList.hidden = "false";
		LoadDoc.hidden = "false";
		
		for (i = 0; i < Responce.length; i++)
		{
			var Option = document.createElement("option");
			Option.value = Responce[i];
			Option.innerHTML = Responce[i];
			DocList.append(Option);
		}
		
	}
	
	function uploadData()
	{
		var message = createMessage();
		var form = createMyForm(message);
		
		sendForm(form, printData, window.location.pathname);
		
		sendForm(new FormData(), makeFileList, "/doc_list");
	}
	
	function saveData(bRewriteCustomer = false)
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		if (bRewriteCustomer)
			form.append("rewrite_customer", "1");
		
		sendForm(form, tryToSave, window.location.pathname + "/save");
	}
	
	function tryToSave(Responce)
	{
		RespMsg = Responce.message;
		if ("rewrite_customer?" == RespMsg)
		{
			res = confirm("Заказчик с таким номером пасспорта уже существует.\n Перезапиать данные?");
			if (res)
			{
				saveData(true);
			}
		}
		else
		{
			Message.innerHTML = RespMsg;
		}
	}
	
	cancelEdit();
	uploadData();
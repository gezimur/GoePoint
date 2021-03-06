    Statuses.innerHTML = "<option value=\"0\">Создан</option>" +
						 "<option value=\"1\">В работе</option>" +
						 "<option value=\"2\">Выполнен</option>";
	
	Statuses.disabled = true;
	Inputs = InputBlock.querySelectorAll("input");
	for (item  = 0; item < Inputs.length; item++)
		Inputs[item].readOnly = true;
	
	function showButtons(Status)
	{
		Buttons = ButtonBlock.querySelectorAll("input");
		if (Status == 0)
		{
			Buttons[0].hidden = false;
			Buttons[1].hidden = true;
			Buttons[2].hidden = true;
		}
		else if (Status == 1)
		{
			Buttons[0].hidden = true;
			Buttons[1].hidden = false;
			Buttons[2].hidden = false;
		}
		else if (Status == 2)
		{
			Buttons[0].hidden = true;
			Buttons[1].hidden = false;
			Buttons[2].hidden = true;
		}
		else if (Status == 3)
		{
			Buttons[0].hidden = true;
			Buttons[1].hidden = true;
			Buttons[2].hidden = true;
		}
	}
	
	function printData(Responce)
	{
		path = window.location.pathname;
		path = path.substr(path.lastIndexOf("/") + 1);
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
			if (Inputs[i].name == "status")
			{
				showButtons(Inputs[i].value);
			}
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
		if ("new" == path || Responce.length < 0)
		{
			DocList.visibility = "hidden";
			LoadDoc.visibility = "hidden";
			return ;
		}
			
		DocList.visibility = "visible";
		LoadDoc.visibility = "visible";
		
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
	
	function changeStatus(Status)
	{		
		var message = createMessage();
		var form = new FormData();

		form.append("status", Status);
		
		sendForm(form, printData, window.location.pathname + "/save");
	}
	
	showButtons(3);
	uploadData();
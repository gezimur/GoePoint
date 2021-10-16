	function editData()
	{
		Title.style.display  = "none";
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
		{
			Inputs[item].readOnly = false;
			if (Inputs[item].name == "full_name")
			{
				Inputs[item].hidden = false;
			}
		}
		
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
		Title.style.display  = "block";
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
		{
			Inputs[item].readOnly = true;
			if (Inputs[item].name == "full_name")
			{
				Inputs[item].hidden = true;
				Title.innerHTML = Inputs[item].value;
			}
		}
		
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
		if (Responce.message == undefined)
			Message.hidden = true;
		else
		{
			Message.hidden = false;
			Message.innerHTML = Responce.message;
		}
		
		JsonTable = Responce.table[0];
		if ("0" == JsonTable.role)
			Role.innerHTML = "Менеджер";
		else if ("1" == JsonTable.role)
			Role.innerHTML = "Инженер";
		
		Inputs = InputBlock.querySelectorAll("input");
		for (i = 0; i < Inputs.length; i++)
		{
			Inputs[i].value = JsonTable[Inputs[i].name];
			if (Inputs[i].name == "full_name")
			{
				Inputs[i].hidden = true;
				Title.innerHTML = Inputs[i].value;
				Title.hidden = false;
			}
		}
	}
	
	function uploadData()
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		sendForm(form, printData, window.location.pathname);
	}
	
	function saveData()
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		sendForm(form, printData, window.location.pathname + "/save");
	}
	
	cancelEdit();
	uploadData();
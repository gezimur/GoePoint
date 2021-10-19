	var SavedParams;
	function editData()
	{
		Title.style.display  = "none";
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
		{
			Inputs[item].readOnly = false;
			if (Inputs[item].name == "full_name")
				Inputs[item].hidden = false;
		}
		
		Buttons = ButtonBlock.querySelectorAll("input");
		for (item  = 0; item < Buttons.length; item++)
		{
			if (Buttons[item].value == "Редактировать")
			{
				Buttons[item].value = "Отмена";
				Buttons[item].onclick = cancelEdit;
			}
			if (Buttons[item].value == "Сохранить")
				Buttons[item].hidden = false;
		}
	}
	function stopEdit()
	{
		Title.style.display  = "block";
		Inputs = InputBlock.querySelectorAll("input");
		for (item  = 0; item < Inputs.length; item++)
		{
			Inputs[item].readOnly = true;
			if (Inputs[item].name == "full_name")
				Inputs[item].hidden = true;
		}
		
		Buttons = ButtonBlock.querySelectorAll("input");
		for (item  = 0; item < Buttons.length; item++)
		{
			if (Buttons[item].value == "Отмена")
			{
				Buttons[item].value = "Редактировать";
				Buttons[item].onclick = editData;
			}
			if (Buttons[item].value == "Сохранить")
				Buttons[item].hidden = true;
		}
	}
	function cancelEdit()
	{
		stopEdit();
		uploadData();
	}
	function showSaved()
	{
		Inputs = InputBlock.querySelectorAll("input");
		for (i = 0; i < Inputs.length; i++)
		{
			Inputs[i].value = SavedParams[Inputs[i].name];
			if (Inputs[i].name == "full_name")
				Title.innerHTML = Inputs[i].value;
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
		
		SavedParams = Responce.table[0];
		
		showSaved();
	}
	
	function uploadData()
	{
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		sendForm(form, printData, window.location.pathname);
	}
	
	function saveData()
	{
		stopEdit();
		
		var message = createMessage();
		var form = createMyForm(message, 0);
		
		sendForm(form, printData, window.location.pathname + "/save");
	}
	
	stopEdit();
	uploadData();
import { useState } from 'react'; 
import axios from "axios";
/*
{
  name:
  price:
  type:
  brand:
}
*/
function AddItems(props){

    const [name, setName] = useState("")
    const [description, setDescription] = useState("")
    const [date, setDate] = useState("")
    const [time, setTime] = useState("")
    const [classification, setClassification] = useState("")
    const [capacity, setCapacity] = useState("")
    const [organizador, setOrganizador] = useState("")

    //funcao disparada no onclick que está la embaixo
    const addItemsButtonPressed = async () => {
      // props.addItems({
      //       "name": name,
      //       "description": description,
      //       "date" : date,
      //       "time" : time,
      //       "type": type,
      //       "classification": classification,
      //       "capacity": capacity
      //   })

      //json que a gtn colocava la no postgres
        const request_body = {
          "nome":name,
          "descricao":description,
          "data":date,
          "horario_inicio":time,
          "horario_fim": time,
          "classificacao_indicativa":classification,
          "lotacao_maxima":capacity,
          //"endereco":
          "organizador_id":organizador
        }
        //pegar o local storage que vai ficar salvo depois que a gnt loga
        var token = localStorage.getItem("token");
        console.log(token);
        const config = { //salvar esse token dentro dessa config
          headers: { Authorization: `Bearer ${token}` }
        };

        try {
          // const response = "TESTE";
          const response = await axios.post("http://localhost:8080/evento/", 
            request_body,
            config
          );
          console.log("Sucesso ao cadastrar Evento: ", response.data);

        } catch (error) {
          console.error("Error signing up:", error);
        }


        //fazer uma tela para listar 

      // apaga os campos
      // setName("")
      // setDescription("")
      // setDate("")
      // setTimeout("")
      // setClassification("")
      // setCapacity("")

    }

  return (
    <div> 
      <div className='container'>
        <div className='row'>
          <h2>Adicionar Evento</h2>
        </div>
        <div className='row'>
          <label>Nome do Evento: </label>
          <input id="name-field" className='form-control' type="text" value={name} onChange={ (e) => setName(e.target.value) }/>
        </div>          
        <div className='row'>
          <label>Descrição: </label>
          <input id="description-field" className='form-control' type="text" value={description} onChange={ (e) => setDescription(e.target.value) }/>
        </div>  
        <div className='row'>
          <label>Data: </label>
          <input id="date-field" className='form-control' type="date" value={date} onChange={ (e) => setDate(e.target.value)}/>
        </div>  
        <div className='row'>
          <label>Horário: </label>
          <input id="time-field" className='form-control' type="time" value={time} onChange={ (e) => setTime(e.target.value)}/>
        </div>       
        <div className='row'>
          <label>Classificação indicativa: </label>
          <input id="classification-field" className='form-control' type="text" value={classification} onChange={ (e) => setClassification(e.target.value) }/>      
        </div> 
        <div className='row'>
          <label>Lotação máxima: </label>
          <input id="capacity-field" className='form-control' type="text" value={capacity} onChange={ (e) => setCapacity(e.target.value) }/>      
        </div>      
        <div className='row'>
          <label>Organizador: </label>
          <input id="capacity-field" className='form-control' type="text" value={organizador} onChange={ (e) => setOrganizador(e.target.value) }/>      
        </div>      
        <div className='row'>
          <button type="button" className='btn btn-dark mt-3' onClick={addItemsButtonPressed}>Adicionar</button>
        </div>
      </div>
    </div>
  )
}

export default AddItems;
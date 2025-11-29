import { useState } from 'react'; 
import axios from "axios";
/*
{
   data
   total
   forma de pagamento
   status
   qnt
}
*/
function AddItems(props){

    const [data, setData] = useState("")
    const [total, setTotal] = useState("")
    const [formPagament, setFormPagament] = useState("")
    const [status, setStatus] = useState("")
    const [qnt, setQnt] = useState("")

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

      // const request_body = {
      //   "nome":"TESTE",
      //   "descricao":"TESTE1",
      //   "data":"2024-10-01",
      //   "horario_inicio":"22:08:28",
      //   "horario_fim": "22:08:28",
      //   "classificacao_indicativa":"1",
      //   "lotacao_maxima":200,
      //   //"endereco":
      //   "organizador":1,
      // }
      // var token = localStorage.getItem("token");
      // console.log(token);
      // const config = {
      //   headers: { Authorization: `Bearer ${token}` }
      // };

      // try {
      //   // const response = "TESTE";
      //   const response = await axios.post("http://localhost:8080/evento/", 
      //     request_body,
      //     config
      //   );
      //   console.log("Sucesso ao cadastrar Evento: ", response.data);
        
      // } catch (error) {
      //   console.error("Error signing up:", error);
      // }

    setData("")
    setTotal("")
    setFormPagament("")
    setTimeout("")
    setStatus("")
    setQnt("")
    }

  return (
    <div> 
      <div className='container'>
        <div className='row'>
          <h2>Adicionar Compra</h2>
        </div>
        <div className='row'>
          <label>Data: </label>
          <input id="name-field" className='form-control' type="text" value={data} onChange={ (e) => setData(e.target.value) }/>
        </div>          
        <div className='row'>
          <label>Total: </label>
          <input id="description-field" className='form-control' type="text" value={total} onChange={ (e) => setTotal(e.target.value) }/>
        </div>  
        <div className='row'>
          <label>Forma de Pagamento: </label>
          <input id="date-field" className='form-control' type="text" value={formPagament} onChange={ (e) => setFormPagament(e.target.value)}/>
        </div>       
        <div className='row'>
          <label>Status: </label>
          <input id="type-field" className='form-control' type="text" value={status} onChange={ (e) => setStatus(e.target.value) }/>
        </div>  
        <div className='row'>
          <label>Quantidade: </label>
          <input id="type-field" className='form-control' type="text" value={qnt} onChange={ (e) => setQnt(e.target.value) }/>
        </div>  
        <div className='row'>
          <button type="button" className='btn btn-dark mt-3' onClick={addItemsButtonPressed}>Adicionar</button>
        </div>
      </div>
    </div>
  )
}

export default AddItems;